package source.view.cli;


import source.models.expressions.*;
import source.models.statements.*;
import source.models.types.BoolType;
import source.models.types.IntType;
import source.models.types.RefType;
import source.models.types.StringType;
import source.models.values.BoolValue;
import source.models.values.IntValue;
import source.models.values.StringValue;
import source.view.command.ExitCommand;
import source.view.command.RunCommand;

import java.util.ArrayList;
import java.util.List;

public class Interpreter {
    public static IStatement firstExample() {
        return new CompoundStatement(
                new VariableDeclarationStatement("v", new BoolType()),
                new CompoundStatement(
                        new AssignStatement("v", new ValueExpression(new BoolValue(true))),
                        new CompoundStatement(
                                new VariableDeclarationStatement("a", new IntType()),
                                new NOPStatement()))
        );
    }

    public static IStatement secondExample() {
        return new CompoundStatement
                (
                        new VariableDeclarationStatement("a", new IntType()),
                        new CompoundStatement
                                (
                                        new VariableDeclarationStatement("b", new IntType()),
                                        new CompoundStatement
                                                (
                                                        new AssignStatement("a",
                                                                new ArithmeticExpression('+',
                                                                        new ValueExpression(new IntValue(2)),
                                                                        new ArithmeticExpression('*',
                                                                                new ValueExpression(new IntValue(3)),
                                                                                new ValueExpression(new IntValue(5)))
                                                                )
                                                        ),
                                                        new CompoundStatement(
                                                                new AssignStatement("b",
                                                                        new ArithmeticExpression('+',
                                                                                new VariableExpression("a"),
                                                                                new ValueExpression(new IntValue(1))
                                                                        )
                                                                ),
                                                                new PrintStatement(new VariableExpression("b"))
                                                        )
                                                )
                                )
                );
    }

    public static IStatement thirdExample() {
        return new CompoundStatement(
                new VariableDeclarationStatement("a", new BoolType()),
                new CompoundStatement(
                        new VariableDeclarationStatement("v", new IntType()),
                        new CompoundStatement(
                                new AssignStatement("a", new ValueExpression(new BoolValue(true))),
                                new CompoundStatement(
                                        new IfStatement(
                                                new VariableExpression("a"),
                                                new AssignStatement("v", new ValueExpression(new IntValue(2))),
                                                new AssignStatement("v", new ValueExpression(new IntValue(3)))
                                        ),
                                        new PrintStatement(
                                                new VariableExpression("v")
                                        )
                                )
                        )
                )
        );
    }

    public static IStatement fourthExample() {
        return new CompoundStatement(
                new VariableDeclarationStatement("varf", new StringType()),
                new CompoundStatement(
                        new AssignStatement("varf", new ValueExpression(new StringValue("test.in"))),
                        new CompoundStatement(
                                new OpenReadFileStatement(new VariableExpression("varf")),
                                new CompoundStatement(
                                        new VariableDeclarationStatement("varc", new IntType()),
                                        new CompoundStatement(
                                                new ReadFileStatement(new VariableExpression("varf"), "varc"),
                                                new CompoundStatement(
                                                        new PrintStatement(new VariableExpression("varc")),
                                                        new CompoundStatement(
                                                                new ReadFileStatement(new VariableExpression("varf"), "varc"),
                                                                new CompoundStatement(
                                                                        new PrintStatement(new VariableExpression("varc")),
                                                                        new CloseReadFileStatement(new VariableExpression("varf"))
                                                                )
                                                        )
                                                )
                                        )
                                )
                        )
                )
        );
    }

    public static IStatement fifthExample() {
        return new CompoundStatement(
                new VariableDeclarationStatement("v", new RefType(new IntType())),
                new CompoundStatement(
                        new AllocateStatement("v", new ValueExpression(new IntValue(20))),
                        new CompoundStatement(
                                new VariableDeclarationStatement("a", new RefType(new RefType(new IntType()))),
                                new CompoundStatement(
                                        new AllocateStatement("a", new VariableExpression("v")),
                                        new CompoundStatement(
                                                new PrintStatement(new VariableExpression("v")),
                                                new PrintStatement(new VariableExpression("a"))
                                        )
                                )
                        )
                )
        );
    }

    public static IStatement sixthExample() {
        return new CompoundStatement(
                new VariableDeclarationStatement("v", new RefType(new IntType())),
                new CompoundStatement(
                        new AllocateStatement("v", new ValueExpression(new IntValue(20))),
                        new CompoundStatement(
                                new VariableDeclarationStatement("a", new RefType(new RefType(new IntType()))),
                                new CompoundStatement(
                                        new AllocateStatement("a", new VariableExpression("v")),
                                        new CompoundStatement(
                                                new PrintStatement(new ReadHeapExpression(new VariableExpression("v"))),
                                                new PrintStatement(new ArithmeticExpression('+',
                                                        new ReadHeapExpression(new ReadHeapExpression(new VariableExpression("a"))),
                                                        new ValueExpression(new IntValue(5))
                                                )
                                                )
                                        )
                                )
                        )
                )
        );
    }

    public static IStatement seventhExample() {
        return new CompoundStatement(
                new VariableDeclarationStatement("v", new RefType(new IntType())),
                new CompoundStatement(
                        new AllocateStatement("v", new ValueExpression(new IntValue(20))),
                        new CompoundStatement(
                                new PrintStatement(new ReadHeapExpression(new VariableExpression("v"))),
                                new CompoundStatement(
                                        new WriteHeapStatement("v", new ValueExpression(new IntValue(30))),
                                        new PrintStatement(new ArithmeticExpression(
                                                '+',
                                                new ReadHeapExpression(new VariableExpression("v")),
                                                new ValueExpression(new IntValue(5))
                                        ))
                                )
                        )
                )
        );
    }

    public static IStatement eighthExample() {
        return new CompoundStatement(
                new VariableDeclarationStatement("v", new RefType(new IntType())),
                new CompoundStatement(
                        new AllocateStatement("v", new ValueExpression(new IntValue(20))),
                        new CompoundStatement(
                                new VariableDeclarationStatement("a", new RefType(new RefType(new IntType()))),
                                new CompoundStatement(
                                        new NOPStatement(),
                                        new CompoundStatement(
                                                new AllocateStatement("v", new ValueExpression(new IntValue(30))),
                                                new PrintStatement(new ReadHeapExpression(
                                                        new ReadHeapExpression(new VariableExpression("a"))
                                                ))
                                        )
                                )
                        )
                )
        );
    }

    public static IStatement ninthExample() {
        return new CompoundStatement(
                new VariableDeclarationStatement("v", new IntType()),
                new CompoundStatement(
                        new AssignStatement("v", new ValueExpression(new IntValue(5))),
                        new CompoundStatement(
                                new WhileStatement(
                                        new RelationalExpression(
                                                new VariableExpression("v"),
                                                new ValueExpression(new IntValue(0)),
                                                ">"
                                        ),
                                        new CompoundStatement(
                                                new PrintStatement(new VariableExpression("v")),
                                                new AssignStatement("v", new ArithmeticExpression(
                                                        '-',
                                                        new VariableExpression("v"),
                                                        new ValueExpression(new IntValue(1))
                                                ))
                                        )
                                ),
                                new PrintStatement(new VariableExpression("v"))
                        )
                )
        );
    }

    public static IStatement threadExample() {
        IStatement forkStatement = new ForkStatement(new CompoundStatement(
                new WriteHeapStatement("a", new ValueExpression(new IntValue(30))),
                new CompoundStatement(
                        new AssignStatement("v", new ValueExpression(new IntValue(32))),
                        new CompoundStatement(
                                new PrintStatement(new VariableExpression("v")),
                                new PrintStatement(new ReadHeapExpression(new VariableExpression("a")))
                        )
                )
        )
        );
        return new CompoundStatement(
                new VariableDeclarationStatement("v", new IntType()),
                new CompoundStatement(
                        new VariableDeclarationStatement("a", new RefType(new IntType())),
                        new CompoundStatement(
                                new AssignStatement("v", new ValueExpression(new IntValue(10))),
                                new CompoundStatement(
                                        new AllocateStatement("a", new ValueExpression(new IntValue(22))),
                                        new CompoundStatement(
                                                forkStatement,
                                                new CompoundStatement(
                                                        new PrintStatement(new VariableExpression("v")),
                                                        new PrintStatement(new ReadHeapExpression(new VariableExpression("a")))
                                                )
                                        )
                                )
                        )
                )
        );
    }

    public static IStatement secondThreadExample() {
        return new CompoundStatement(
                new VariableDeclarationStatement("a", new RefType(new IntType())),
                new CompoundStatement(
                        new VariableDeclarationStatement("counter", new IntType()),
                        new WhileStatement(
                                new RelationalExpression(
                                        new VariableExpression("counter"),
                                        new ValueExpression(new IntValue(10)),
                                        "<"
                                ),
                                new CompoundStatement(
                                        new ForkStatement(
                                                new ForkStatement(
                                                        new CompoundStatement(
                                                                new AllocateStatement("a", new VariableExpression("counter")),
                                                                new PrintStatement(new ReadHeapExpression(new VariableExpression("a")))
                                                        )
                                                )
                                        ),
                                        new AssignStatement(
                                                "counter",
                                                new ArithmeticExpression(
                                                        '+',
                                                        new VariableExpression("counter"),
                                                        new ValueExpression(new IntValue(1))
                                                )
                                        )
                                )
                        )
                )
        );
    }


    public static IStatement switchExample(){
        return new CompoundStatement(new VariableDeclarationStatement("a", new IntType()),
                new CompoundStatement(new VariableDeclarationStatement("b", new IntType()),
                        new CompoundStatement(new VariableDeclarationStatement("c", new IntType()),
                                new CompoundStatement(new AssignStatement("a", new ValueExpression(new IntValue(1))),
                                        new CompoundStatement(new AssignStatement("b", new ValueExpression(new IntValue(2))),
                                                new CompoundStatement(new AssignStatement("c", new ValueExpression(new IntValue(5))),
                                                        new CompoundStatement(new SwitchStatement(
                                                                new ArithmeticExpression('*', new VariableExpression("a"), new ValueExpression(new IntValue(10))),
                                                                new ArithmeticExpression('*', new VariableExpression("b"), new VariableExpression("c")),
                                                                new CompoundStatement(new PrintStatement(new VariableExpression("a")), new PrintStatement(new VariableExpression("b"))),
                                                                new ValueExpression(new IntValue(10)),
                                                                new CompoundStatement(new PrintStatement(new ValueExpression(new IntValue(100))), new PrintStatement(new ValueExpression(new IntValue(200)))),
                                                                new PrintStatement(new ValueExpression(new IntValue(300)))
                                                        ), new PrintStatement(new ValueExpression(new IntValue(300))))))))));

    }

    public static IStatement semaphoreExample(){
        return new CompoundStatement(
                new VariableDeclarationStatement("v1", new RefType(new IntType())),
                new CompoundStatement(
                        new VariableDeclarationStatement("cnt", new IntType()),
                        new CompoundStatement(
                                new AllocateStatement("v1", new ValueExpression(new IntValue(1))),
                                new CompoundStatement(
                                        new CreateSemaphoreStatement("cnt", new ReadHeapExpression(new VariableExpression("v1"))),
                                        new CompoundStatement(
                                                new ForkStatement(
                                                        new CompoundStatement(
                                                                new AcquireStatement("cnt"),
                                                                new CompoundStatement(
                                                                        new WriteHeapStatement("v1", new ArithmeticExpression('*', new ReadHeapExpression(new VariableExpression("v1")), new ValueExpression(new IntValue(10)))),
                                                                        new CompoundStatement(
                                                                                new PrintStatement(new ReadHeapExpression(new VariableExpression("v1"))),
                                                                                new ReleaseStatement("cnt")
                                                                        )
                                                                )
                                                        )
                                                ),
                                                new CompoundStatement(
                                                        new ForkStatement(
                                                                new CompoundStatement(
                                                                        new AcquireStatement("cnt"),
                                                                        new CompoundStatement(
                                                                                new WriteHeapStatement("v1", new ArithmeticExpression('*',  new ReadHeapExpression(new VariableExpression("v1")), new ValueExpression(new IntValue(10)))),
                                                                                new CompoundStatement(
                                                                                        new WriteHeapStatement("v1", new ArithmeticExpression('*', new ReadHeapExpression(new VariableExpression("v1")), new ValueExpression(new IntValue(2)))),
                                                                                        new CompoundStatement(
                                                                                                new PrintStatement(new ReadHeapExpression(new VariableExpression("v1"))),
                                                                                                new ReleaseStatement("cnt")
                                                                                        )
                                                                                )
                                                                        )
                                                                )
                                                        ),
                                                        new CompoundStatement(
                                                                new AcquireStatement("cnt"),
                                                                new CompoundStatement(
                                                                        new PrintStatement(new ArithmeticExpression('-', new ReadHeapExpression(new VariableExpression("v1")), new ValueExpression(new IntValue(1)))),
                                                                        new ReleaseStatement("cnt")
                                                                )
                                                        )
                                                )
                                        )
                                )
                        )
                )
        );
    }
    public static List<IStatement> getAllExamples()
    {
        ArrayList<IStatement> allStatements = new ArrayList<>();

        allStatements.add(firstExample());
        allStatements.add(secondExample());
        allStatements.add(thirdExample());
        allStatements.add(fourthExample());
        allStatements.add(fifthExample());
        allStatements.add(sixthExample());
        allStatements.add(seventhExample());
        allStatements.add(eighthExample());
        allStatements.add(ninthExample());
        allStatements.add(threadExample());
        allStatements.add(secondThreadExample());

        allStatements.add(switchExample());

        allStatements.add(semaphoreExample());

        return allStatements;
    }
    public void runView() {
        IStatement firstStatement = firstExample();
        IStatement secondStatement = secondExample();
        IStatement thirdStatement = thirdExample();
        IStatement fourthStatement = fourthExample();
        IStatement fifthStatement = fifthExample();
        IStatement sixthStatement = sixthExample();
        IStatement seventhStatement = seventhExample();
        IStatement eighthStatement = eighthExample();
        IStatement ninthStatement = ninthExample();
        IStatement threadStatement = threadExample();
        IStatement secondThreadStatement = secondThreadExample();

        IStatement switchStatement = switchExample();

        IStatement semaphoreStatement = semaphoreExample();

        TextMenu menu = new TextMenu();
        menu.addCommand(new ExitCommand("0", "Exit"));
        menu.addCommand(new RunCommand("1", "First Example", firstStatement));
        menu.addCommand(new RunCommand("2", "Second Example", secondStatement));
        menu.addCommand(new RunCommand("3", "Third Example", thirdStatement));
        menu.addCommand(new RunCommand("4", "Fourth Example", fourthStatement));
        menu.addCommand(new RunCommand("5", "Fifth Example", fifthStatement));
        menu.addCommand(new RunCommand("6", "Sixth Example", sixthStatement));
        menu.addCommand(new RunCommand("7", "Seventh Example", seventhStatement));
        menu.addCommand(new RunCommand("8", "Eighth Example", eighthStatement));
        menu.addCommand(new RunCommand("9", "Ninth Example", ninthStatement));
        menu.addCommand(new RunCommand("10", "Threads Example", threadStatement));
        menu.addCommand(new RunCommand("11", "Second Threads Example", secondThreadStatement));

        menu.addCommand(new RunCommand("12", "Switch Example", switchStatement));

        menu.addCommand(new RunCommand("13", "Count Semaphore Example", semaphoreStatement));

        menu.show();
    }
}
