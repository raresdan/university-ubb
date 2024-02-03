package source.controller.view_controllers;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.Region;
import javafx.stage.Stage;
import source.exceptions.InterpreterException;
import source.models.statements.IStatement;
import source.models.utils.MyDictionary;
import source.view.cli.Interpreter;
import source.view.gui.Main;

import java.io.IOException;

public class SelectProgramController {
    @FXML
    private ListView<IStatement> programsList;

    @FXML
    private Button executeButton;

    @FXML
    public void initialize()
    {
        ObservableList<IStatement> allPrograms = FXCollections.observableArrayList(Interpreter.getAllExamples());
        programsList.setItems(allPrograms);
        programsList.getSelectionModel().setSelectionMode(SelectionMode.SINGLE);
        programsList.setOnMouseClicked(
                event -> {
                    if (event.getClickCount() == 2)
                        executeButtonHandler();
                }
        );
    }

    private void openProgramWindow(IStatement selectedProgram)
    {
        try {
            FXMLLoader programLoader = new FXMLLoader(Main.class.getResource("/source/program-view.fxml"));
            Parent root;
            selectedProgram.typeCheck(new MyDictionary<>());
            root = programLoader.load();
            ProgramController controller = programLoader.getController();
            controller.setProgramStatement(selectedProgram);
            Stage programStage = new Stage();
            programStage.setTitle("Program window!");
            programStage.setScene(new Scene(root));
            programStage.show();
        }
        catch (IOException | InterpreterException e)
        {
            Alert alert = new Alert(Alert.AlertType.ERROR, e.getMessage(), ButtonType.OK);
            alert.getDialogPane().setMinHeight(Region.USE_PREF_SIZE);
            alert.showAndWait();
        }
    }

    @FXML
    public void executeButtonHandler() {
        int index = programsList.getSelectionModel().getSelectedIndex();
        if (index < 0)
            return;
        IStatement selectedProgram = Interpreter.getAllExamples().get(index);
        if (selectedProgram == null)
            return;
        this.openProgramWindow(selectedProgram);
    }

}

