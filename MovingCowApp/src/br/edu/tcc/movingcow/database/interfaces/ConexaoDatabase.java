/**
 * 
 */
package br.edu.tcc.movingcow.database.interfaces;

import java.sql.Connection;

/**
 * @author MatheusMahl
 *
 */
public interface ConexaoDatabase {
	
	Connection getConexao();

}
