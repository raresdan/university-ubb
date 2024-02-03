module source {
    requires javafx.controls;
    requires javafx.fxml;


    opens source to javafx.fxml;
    //exports source;
    exports source.controller;
    opens source.controller to javafx.fxml;
    exports source.view.gui;
    opens source.view.gui to javafx.fxml;
    exports source.controller.view_controllers;
    opens source.controller.view_controllers to javafx.fxml;
}