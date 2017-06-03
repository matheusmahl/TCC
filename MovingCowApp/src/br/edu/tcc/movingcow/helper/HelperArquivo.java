/**
 * 
 */
package br.edu.tcc.movingcow.helper;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

/**
 * @author MatheusMahl
 *
 */
public class HelperArquivo {

  public static ArrayList<String> LerArquivo(String nomeArquivo) {

    ArrayList<String> arrayRetorno = new ArrayList<>();

    File arquivo = new File(nomeArquivo);
    if (!arquivo.exists()) {
      System.out.println("Arquivo não existe.");
    }

    try {
      BufferedReader lerArq = new BufferedReader(new FileReader(arquivo));
      String linha = null;
      do {
        linha = lerArq.readLine();
        arrayRetorno.add(linha);
      } while (linha != null);

      lerArq.close();
    } catch (FileNotFoundException e) {
      // TODO Auto-generated catch block
      e.printStackTrace();
    } catch (IOException e) {
      // TODO Auto-generated catch block
      e.printStackTrace();
    }

    return arrayRetorno;
  }

}
