package br.edu.tcc.movingcow.model;

import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;

/**
 * @author MatheusMahl
 *
 */

public class Cow {

  private final StringProperty data;
  private final StringProperty hora;
  private final StringProperty x;
  private final StringProperty y;
  private final StringProperty z;

  public Cow() {
    this(null, null, null, null, null);
  }

  public Cow(String data, String hora, String x, String y, String z) {
    this.data = new SimpleStringProperty(data);
    this.hora = new SimpleStringProperty(hora);
    this.x = new SimpleStringProperty(x);
    this.y = new SimpleStringProperty(y);
    this.z = new SimpleStringProperty(z);
  }

  public String getData() {
    return data.get();
  }

  public void setData(String data) {
    this.data.set(data);
  }

  public StringProperty dataProperty() {
    return data;
  }

  public String getHora() {
    return hora.get();
  }

  public void setHora(String hora) {
    this.hora.set(hora);
  }

  public StringProperty horaProperty() {
    return hora;
  }

  public StringProperty xProperty() {
    return x;
  }

  public String getX() {
    return x.get();
  }

  public void setX(String x) {
    this.x.set(x);
  }

  public StringProperty yProperty() {
    return y;
  }

  public String getY() {
    return y.get();
  }

  public void setY(String y) {
    this.y.set(y);
  }

  public StringProperty zProperty() {
    return z;
  }

  public String getZ() {
    return z.get();
  }

  public void setZ(String z) {
    this.z.set(z);
  }

}