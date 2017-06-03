/**
 * 
 */
package br.edu.tcc.movingcow.cow.controller;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.Date;
import java.util.regex.Pattern;

import br.edu.tcc.movingcow.Main;
import br.edu.tcc.movingcow.helper.HelperArquivo;
import br.edu.tcc.movingcow.model.Cow;
import br.edu.tcc.movingcow.regras.MovimentacaoBovinos;
import br.edu.tcc.movingcow.regras.RgnMovimentacao;
import javafx.fxml.FXML;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;

/**
 * @author MatheusMahl
 *
 */
public class CowController {

  @FXML
  private TableView<Cow> tableView;
  
  @FXML
  private TableColumn<Cow, String> dataColumn;
  @FXML
  private TableColumn<Cow, String> horaColumn;
  @FXML
  private TableColumn<Cow, String> xColumn;
  @FXML
  private TableColumn<Cow, String> yColumn;
  @FXML
  private TableColumn<Cow, String> zColumn;
  
  @FXML
  private TextField txtDataLeitura;
  @FXML
  private TextField txtHoraInicial;
  @FXML
  private TextField txtHoraFinal;
  @FXML
  private TextArea txaCalculos;
  
  
  private Main main;
  
  public CowController() {
   
  }

  @FXML
  private void initialize() {
    dataColumn.setCellValueFactory(cellData -> cellData.getValue().dataProperty());
    horaColumn.setCellValueFactory(cellData -> cellData.getValue().horaProperty());
    xColumn.setCellValueFactory(cellData -> cellData.getValue().xProperty());
    yColumn.setCellValueFactory(cellData -> cellData.getValue().yProperty());
    zColumn.setCellValueFactory(cellData -> cellData.getValue().zProperty());
  }
  
  
  @FXML
  private void handleCarregarDados() {
    try {
      CarregarDados();
    } catch (ParseException e) {
      // TODO Auto-generated catch block
      e.printStackTrace();
    }  
  }
 
  public void setMainApp(Main main) {
    this.main = main;

    // Adiciona os dados da observable list na tabela
    tableView.setItems(main.getMovimentacaoDados());
}
  
  public void CarregarDados() throws ParseException {
    main.getMovimentacaoDados().clear();
    ArrayList<String> array = new ArrayList<>();
    String dataArquivo = "";
    dataArquivo = txtDataLeitura.getText(); //new SimpleDateFormat("ddMMyyyy").parse(

    
    
    String arquivo = "C:\\TCC\\leituras\\" + dataArquivo + "\\" + dataArquivo  + ".TXT";
    array = HelperArquivo.LerArquivo(arquivo);
   
    Date horaInicial = new SimpleDateFormat("HHmmss").parse(txtHoraInicial.getText());
    Date horaFinal = new SimpleDateFormat("HHmmss").parse(txtHoraFinal.getText());
    
    for (int i = 0; i < array.size() - 1; i++) {

      String[] matriz = new String[5];
      String string = array.get(i);

      matriz = string.split("[" + Pattern.quote("|N") + "]");

      String data = null;
      String hora = null;
      try {
               
        Date horaRegistro = new SimpleDateFormat("HHmmss").parse(matriz[1]);
    
        if ((horaRegistro.before(horaInicial)) || (horaRegistro.after(horaFinal))){
          continue;
        }
        
        data = new SimpleDateFormat("dd/MM/yyyy").format(new SimpleDateFormat("ddMMyyyy").parse(matriz[0]));
        hora = new SimpleDateFormat("HH:mm:ss").format(horaRegistro);

      } catch (ParseException e) {
        // TODO Auto-generated catch block
        e.printStackTrace();
      }     
      
      if (data != null) {
        matriz[0] = data;
      }

      if (hora != null) {
        matriz[1] = hora;
      }

      /*matriz[2] = Double.toString(Integer.parseInt(matriz[2]));// +
                                                                      // "m/s²";
      matriz[3] = Double.toString(Integer.parseInt(matriz[3]));// +
                                                                      // "m/s²";
      matriz[4] = Double.toString(Integer.parseInt(matriz[4]));// +*/

      main.getMovimentacaoDados().add(new Cow(matriz[0], matriz[1], matriz[2], matriz[3], matriz[4]));
      
    }    
    
    new MovimentacaoBovinos().calcular(main.getMovimentacaoDados(), txaCalculos);

  }

}
