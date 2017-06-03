/**
 * 
 */
package br.edu.tcc.movingcow.regras;

import java.text.ParseException;

import br.edu.tcc.movingcow.model.Cow;
import javafx.collections.ObservableList;
import javafx.scene.control.TextArea;

/**
 * @author MatheusMahl
 *
 */
public interface RgnMovimentacao {
  public void calcular(ObservableList<Cow> lista, TextArea saida) throws ParseException;
    
}
