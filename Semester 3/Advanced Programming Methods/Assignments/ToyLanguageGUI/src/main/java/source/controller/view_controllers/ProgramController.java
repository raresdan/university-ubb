package source.controller.view_controllers;

import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.collections.FXCollections;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.layout.Region;
import source.controller.Controller;
import source.exceptions.ExpressionEvaluationException;
import source.exceptions.InterpreterException;
import source.exceptions.StackException;
import source.exceptions.StatementException;
import source.models.PrgState;
import source.models.statements.IStatement;
import source.models.utils.MyHeap;
import source.models.utils.MyIHeap;
import source.models.utils.MyIList;
import source.models.utils.MyList;
import source.models.values.IValue;
import source.repository.IRepository;
import source.repository.ProgramsRepository;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class ProgramController {
    private IStatement programStatement;
    private Controller controller;

    @FXML
    private TextField numberOfPrgStates;

    @FXML
    private TableView<Pair<Integer, IValue>> heapTableView;

    @FXML
    private TableColumn<Pair<Integer, IValue>, Integer> heapAddressColumn;

    @FXML
    private TableColumn<Pair<Integer, IValue>, String> heapValueColumn;

    @FXML
    private ListView<IValue> outputListView;

    @FXML
    private ListView<String> fileTableView;

    @FXML
    private ListView<Integer> prgStatesIdentifiersView;

    @FXML
    private ListView<String> exeStackView;

    @FXML
    private TableView<Pair<String, IValue>> symTableView;

    @FXML
    private TableColumn<Pair<String, IValue>, String> variableNameColumn;

    @FXML
    private TableColumn<Pair<String, IValue>, String> symValueColumn;

    @FXML
    private Button oneStepButton;

    @FXML
    private void initialize()
    {
        heapAddressColumn.setCellValueFactory(pair -> new SimpleIntegerProperty(pair.getValue().first).asObject());
        heapValueColumn.setCellValueFactory(pair -> new SimpleStringProperty(pair.getValue().second.toString()));
        variableNameColumn.setCellValueFactory(pair -> new SimpleStringProperty(pair.getValue().first));
        symValueColumn.setCellValueFactory(pair -> new SimpleStringProperty(pair.getValue().second.toString()));
    }

    public void setProgramStatement(IStatement programStatement)
    {
        this.programStatement = programStatement;
        this.numberOfPrgStates.setText(programStatement.toString());
        PrgState currentProgram = new PrgState(programStatement);
        IRepository programRepository = new ProgramsRepository("log.txt");
        programRepository.addProgram(currentProgram);
        this.controller = new Controller(programRepository);
        this.populate();
    }

    @FXML
    private void handleOneStepButton()
    {
        if (this.controller.getAllPrograms().isEmpty())
        {
            Alert alert = new Alert(Alert.AlertType.ERROR, "Nothing to execute!", ButtonType.OK);
            alert.getDialogPane().setMinHeight(Region.USE_PREF_SIZE);
            alert.showAndWait();
            return;
        }
        try
        {
            this.controller.oneStepAll();
            populate();
        }
        catch(InterpreterException e)
        {
            populate();
            Alert alert = new Alert(Alert.AlertType.ERROR, e.getMessage(), ButtonType.OK);
            alert.getDialogPane().setMinHeight(Region.USE_PREF_SIZE);
            alert.showAndWait();
        }
    }

    @FXML
    private void handleAllStepsButton()
    {
        if (this.controller.getAllPrograms().isEmpty())
        {
            Alert alert = new Alert(Alert.AlertType.ERROR, "Nothing to execute!", ButtonType.OK);
            alert.getDialogPane().setMinHeight(Region.USE_PREF_SIZE);
            alert.showAndWait();
            return;
        }
        try {
            this.controller.allSteps();
            populate();
        }
        catch (InterpreterException | IOException | ExpressionEvaluationException | StatementException | StackException e)
        {
            populate();
            Alert alert = new Alert(Alert.AlertType.ERROR, e.getMessage(), ButtonType.OK);
            alert.getDialogPane().setMinHeight(Region.USE_PREF_SIZE);
            alert.showAndWait();
        }
    }

    @FXML
    private void populate()
    {
        this.populateHeap();
        this.populateOutputList();
        this.populateFileTableList();
        this.populateProgramStatesIdentifiers();
        this.populateSymbolTableView();
        this.populateExecutionStack();
    }

    private void populateHeap()
    {
        MyIHeap currentHeap = new MyHeap();
        if (!controller.getAllPrograms().isEmpty())
            currentHeap = controller.getAllPrograms().getFirst().getHeapTable();
        List<Pair<Integer, IValue>> heapTablePairs = new ArrayList<>();
        for (Map.Entry<Integer, IValue> entry : currentHeap.getContent().entrySet())
            heapTablePairs.add(new Pair<>(entry.getKey(), entry.getValue()));
        this.heapTableView.setItems(FXCollections.observableArrayList(heapTablePairs));
        this.heapTableView.refresh();
    }

    private void populateOutputList()
    {
        MyIList<IValue> outputList = new MyList<>();
        if (!controller.getAllPrograms().isEmpty())
            outputList = controller.getAllPrograms().getFirst().getOutputList();
        else if (controller.getCopyProgram() != null)
            outputList = controller.getCopyProgram().getOutputList();
        this.outputListView.setItems(FXCollections.observableArrayList(outputList.getOutput()));
        this.outputListView.refresh();
    }

    private void populateFileTableList()
    {
        List<String> files = new ArrayList<>();
        if (!controller.getAllPrograms().isEmpty())
            files = new ArrayList<>(controller.getAllPrograms().getFirst().getFileTable().getKeySet());
        else if (controller.getCopyProgram() != null)
            files = new ArrayList<>(controller.getCopyProgram().getFileTable().getKeySet());
        this.fileTableView.setItems(FXCollections.observableArrayList(files));
        this.fileTableView.refresh();
    }

    private void populateProgramStatesIdentifiers()
    {
        List<PrgState> programStates = this.controller.getAllPrograms();
        List<Integer> idList = programStates.stream()
                .map(PrgState::getId)
                .collect(Collectors.toList());
        this.prgStatesIdentifiersView.setItems(FXCollections.observableArrayList(idList));
        this.prgStatesIdentifiersView.refresh();
        if (programStates.size() > 1)
            this.numberOfPrgStates.setText("There are: " + programStates.size() + " programs!");
        else
            this.numberOfPrgStates.setText("There is one program!");
    }

    private PrgState getCurrentProgram()
    {
        if (this.controller.getAllPrograms().isEmpty())
            return null;
        int selectedId = prgStatesIdentifiersView.getSelectionModel().getSelectedIndex();
        if (selectedId == -1)
            return this.controller.getAllPrograms().getFirst();
        return this.controller.getAllPrograms().get(selectedId);
    }

    private void populateSymbolTableView()
    {
        PrgState currentProgram = this.getCurrentProgram();
        List<Pair<String, IValue>> symbolTableList = new ArrayList<>();
        if (currentProgram != null)
            for (Map.Entry<String, IValue> entry : currentProgram.getSymbolTable().getContent().entrySet())
                symbolTableList.add(new Pair<>(entry.getKey(), entry.getValue()));
        this.symTableView.setItems(FXCollections.observableArrayList(symbolTableList));
        this.symTableView.refresh();
    }

    private void populateExecutionStack()
    {
        PrgState currentProgram = this.getCurrentProgram();
        List<String> exeStackList = new ArrayList<>();
        if (currentProgram != null)
            for (IStatement currentStatement : currentProgram.getStackStatements())
                exeStackList.add(currentStatement.toString());
        this.exeStackView.setItems(FXCollections.observableArrayList(exeStackList));
        this.exeStackView.refresh();
    }
}
