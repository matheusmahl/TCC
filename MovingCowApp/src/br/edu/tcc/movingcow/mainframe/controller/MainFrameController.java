/**
 * 
 */
package br.edu.tcc.movingcow.mainframe.controller;

import br.edu.tcc.movingcow.Main;
import javafx.fxml.FXML;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.layout.VBoxBuilder;
import javafx.scene.text.Text;
import javafx.stage.Modality;
import javafx.stage.Stage;

/**
 * @author MatheusMahl
 *
 */
public class MainFrameController {

  private Main mainApp;

  @FXML
  private void initialize() {

  }

  @FXML
  private void handleShowStatistics() {
    mainApp.showEstatisticas();
  }

  @FXML
  private void handleCarregarDados() {
    
  }

  @FXML
  private void handleAbout() {
    Stage dialogStage = new Stage();
    dialogStage.initModality(Modality.WINDOW_MODAL);
    
    Scene scene = new Scene(VBoxBuilder.create().children(new Text("Hi"), new Button("Ok.")).alignment(Pos.CENTER).padding(new Insets(5)).build());
    
    dialogStage.setScene(scene);
    dialogStage.show();

  }

  public void setMainApp(Main mainApp) {
    this.mainApp = mainApp;
  }
}
