/**
 * 
 */
package br.edu.tcc.movingcow.regras;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.GregorianCalendar;

import br.edu.tcc.movingcow.model.Cow;
import javafx.collections.ObservableList;
import javafx.scene.control.TextArea;

/**
 * @author MatheusMahl
 *
 */
public class MovimentacaoBovinos implements RgnMovimentacao {
  
  private static final int LIMITE_INFERIOR_Y = 15000;
  private static final int LIMITE_SUPERIOR_Y = 17000;
  private static final int LIMITE_INFERIOR_X = -2500;
  private static final int LIMITE_SUPERIOR_X = 2500;

  /* (non-Javadoc)
   * @see br.edu.tcc.movingcow.regras.RgnMovimentacao#calcular(javafx.collections.ObservableList, javafx.scene.control.TextArea)
   */
  @Override
  public void calcular(ObservableList<Cow> lista, TextArea saida) throws ParseException {
    GregorianCalendar tempoSemMovimentacao = new GregorianCalendar();
    tempoSemMovimentacao.setTime(new SimpleDateFormat("HHmmss").parse("000000"));
    GregorianCalendar tempoEmMovimentacao = new GregorianCalendar();
    tempoEmMovimentacao.setTime(new SimpleDateFormat("HHmmss").parse("000000"));
    
    for(Cow vaca : lista) {
      //Date hora = new SimpleDateFormat("HHmmss").parse(vaca.getHora());
      int valorY = Integer.parseInt(vaca.getY());
      int valorX = Integer.parseInt(vaca.getX());
      if ((valorY > LIMITE_INFERIOR_Y) && (valorY < LIMITE_SUPERIOR_Y) && 
          (valorX > LIMITE_INFERIOR_X) && (valorX < LIMITE_SUPERIOR_X)){
        tempoSemMovimentacao.add(Calendar.SECOND, 2);
      } else {
        tempoEmMovimentacao.add(Calendar.SECOND, 2);
      }           
      
    }
    
    String segundosSemMov = new SimpleDateFormat("HH:mm:ss").format(tempoSemMovimentacao.getTime());
    String segundosEmMov = new SimpleDateFormat("HH:mm:ss").format(tempoEmMovimentacao.getTime());
    saida.clear();
    saida.appendText("Tempo sem movimentacao: " + segundosSemMov + "\n");
    saida.appendText("Tempo em movimentacao: " + segundosEmMov +  "\n");
    
    double metrosporsegundo = 1.8 / 3.6;
    float tempoEmSegundos = (tempoEmMovimentacao.get(Calendar.HOUR_OF_DAY) * 3600) + (tempoEmMovimentacao.get(Calendar.MINUTE) * 60) + tempoEmMovimentacao.get(Calendar.SECOND);
        
    double metrosPercorridos = tempoEmSegundos * metrosporsegundo;
    
    
    saida.appendText("Metros percorridos: " + metrosPercorridos +  "\n");
  }

}
