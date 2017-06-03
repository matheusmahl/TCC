package br.edu.tcc.movingcow.estatisticas.controller;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Arrays;
import java.util.Date;
import java.util.List;

import br.edu.tcc.movingcow.model.Cow;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.chart.CategoryAxis;
import javafx.scene.chart.LineChart;
import javafx.scene.chart.XYChart;

public class EstatisticasController {

  @FXML
  private LineChart<String, Double> lineChart;

  @FXML
  private CategoryAxis xAxis;

  //private ObservableList<String> listaTemperaturas = FXCollections.observableArrayList();

  /**
   * Inicializa a classe controller. Eeste método é chamado automaticamente após
   * o arquivo fxml ter sido carregado.
   */
  @FXML
  private void initialize() {
    // String[] temperaturas = { "00:00:00", "07:00:00", "09:00:00", "11:00:00",
    // "13:00:00", "15:00:00", "17:00:00", "19:00:00", "21:00:00", "23:00:00" };

    // listaTemperaturas.addAll(Arrays.asList(temperaturas));

    // Associa as temperaturas como categorias para o eixo horizontal.
    // xAxis.setCategories(listaTemperaturas);

    lineChart.setTitle("Movimentação bovina");
  }

  public void setPersonData(List<Cow> cows) {

    XYChart.Series<String, Double> seriesX = new XYChart.Series<>();
    XYChart.Series<String, Double> seriesY = new XYChart.Series<>();
    XYChart.Series<String, Double> seriesZ = new XYChart.Series<>();

    seriesX.setName("X");

    seriesY.setName("Y");
    seriesZ.setName("Z");

    for (Cow cow : cows) {
      try {
        

          seriesX.getData().add(new XYChart.Data<>(cow.getHora(), Double.parseDouble(cow.getX())));
          seriesY.getData().add(new XYChart.Data<>(cow.getHora(), Double.parseDouble(cow.getY())));
          seriesZ.getData().add(new XYChart.Data<>(cow.getHora(), Double.parseDouble(cow.getZ())));
        
      } catch (NumberFormatException e) {
        // TODO Auto-generated catch block
        e.printStackTrace();
      }

    }

    lineChart.getData().add(seriesX);
    lineChart.getData().add(seriesY);
    lineChart.getData().add(seriesZ);
  }
}
