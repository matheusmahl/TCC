package br.edu.tcc.movingcow;

import java.io.IOException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.regex.Pattern;

import br.edu.tcc.movingcow.cow.controller.CowController;
import br.edu.tcc.movingcow.estatisticas.controller.EstatisticasController;
import br.edu.tcc.movingcow.helper.HelperArquivo;
import br.edu.tcc.movingcow.mainframe.controller.MainFrameController;
import br.edu.tcc.movingcow.model.Cow;
import javafx.application.Application;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.image.Image;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.BorderPane;
import javafx.stage.Modality;
import javafx.stage.Stage;

public class Main extends Application {

  private Stage primaryStage;
  private BorderPane rootLayout;
  private ObservableList<Cow> movimentacaoDados = FXCollections.observableArrayList();

  @Override
  public void start(Stage primaryStage) {
    this.primaryStage = primaryStage;
    this.primaryStage.setTitle("MovingCowApp");
    this.primaryStage.getIcons().add(new Image("resources/images/cow.png"));

    initRootLayout();

    showCowOverview();
  }

  public static void main(String[] args) {
    launch(args);
  }

  private void initRootLayout() {
    try {
      // Carrega o root layout do arquivo fxml.
      FXMLLoader loader = new FXMLLoader();
      loader.setLocation(Main.class.getResource("view/MainFrame.fxml"));
      rootLayout = (BorderPane) loader.load();

      // Mostra a scene (cena) contendo o root layout.
      Scene scene = new Scene(rootLayout);
      primaryStage.setScene(scene);

      // Dá ao controller o acesso ao main app.
      MainFrameController controller = loader.getController();
      controller.setMainApp(this);

      primaryStage.show();
    } catch (IOException e) {
      e.printStackTrace();
    }
  }

  /**
   * Mostra o person overview dentro do root layout.
   */
  public void showCowOverview() {
    try {
      // Carrega o person overview.
      FXMLLoader loader = new FXMLLoader();
      loader.setLocation(Main.class.getResource("view/CowOverview.fxml"));
      AnchorPane cowOverview = (AnchorPane) loader.load();

      // Define o person overview dentro do root layout.
      rootLayout.setCenter(cowOverview);

      // Dá ao controlador acesso à the main app.
      CowController controller = loader.getController();
      controller.setMainApp(this);

    } catch (IOException e) {
      e.printStackTrace();
    }
  }

  public Stage getPrimaryStage() {
    return primaryStage;
  }

  public void showEstatisticas() {
    try {
      // Carrega o arquivo fxml e cria um novo palco para o popup.
      FXMLLoader loader = new FXMLLoader();
      loader.setLocation(Main.class.getResource("estatisticas/view/EstatisticasOverview.fxml"));
      AnchorPane page = (AnchorPane) loader.load();
      Stage dialogStage = new Stage();
      dialogStage.setTitle("Estatisticas");
      dialogStage.initModality(Modality.WINDOW_MODAL);
      dialogStage.initOwner(primaryStage);
      Scene scene = new Scene(page);
      dialogStage.setScene(scene);

      // Define a pessoa dentro do controller.
      EstatisticasController controller = loader.getController();
      controller.setPersonData(getMovimentacaoDados());

      dialogStage.show();

    } catch (IOException e) {
      e.printStackTrace();
    }
  }

 

  public ObservableList<Cow> getMovimentacaoDados() {
    return movimentacaoDados;
  }

}
