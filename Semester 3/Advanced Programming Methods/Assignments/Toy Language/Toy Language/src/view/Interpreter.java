package view;


import models.expressions.*;
import models.statements.*;
import models.types.*;
import models.values.BoolValue;
import models.values.IntValue;
import models.values.StringValue;
import view.command.ExitCommand;
import view.command.RunCommand;

public class Interpreter {
    public IStatement firstExample() {
        return new CompoundStatement(
                new VariableDeclarationStatement("v", new BoolType()),
                new CompoundStatement(
                        new AssignStatement("v", new ValueExpression(new BoolValue(true))),
                        new CompoundStatement(
                                new VariableDeclarationStatement("a", new IntType()),
                                new NOPStatement()))
        );
    }

    public IStatement secondExample() {
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

    public IStatement thirdExample() {
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

    public IStatement fourthExample() {
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

    public IStatement fifthExample() {
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

    public IStatement sixthExample() {
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

    public IStatement seventhExample() {
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

    public IStatement eighthExample() {
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

    public IStatement ninthExample() {
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

    public IStatement threadExample() {
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

    public IStatement secondThreadExample() {
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
    public void runView() {
        IStatement firstStatement = this.firstExample();
        IStatement secondStatement = this.secondExample();
        IStatement thirdStatement = this.thirdExample();
        IStatement fourthStatement = this.fourthExample();
        IStatement fifthStatement = this.fifthExample();
        IStatement sixthStatement = this.sixthExample();
        IStatement seventhStatement = this.seventhExample();
        IStatement eighthStatement = this.eighthExample();
        IStatement ninthStatement = this.ninthExample();
        IStatement threadStatement = this.threadExample();
        IStatement secondThreadStatement = this.secondThreadExample();

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

        menu.show();
    }
}
