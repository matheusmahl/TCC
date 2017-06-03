package br.edu.tcc.movingcow.database;

import java.sql.Connection;
import java.sql.DriverManager;

import br.edu.tcc.movingcow.database.interfaces.ConexaoDatabase;


/**
 * @author MatheusMahl
 * 
 */
public class ConexaoFirebird implements ConexaoDatabase {
	private Connection conexao = null;

	public Connection getConexao() {
		if (conexao == null) {
			try {
				String driver = "org.firebirdsql.jdbc.FBDriver";
				Class.forName(driver);

				String serverName = "localhost";
				String porta = "3050";
				String database = "C:/database/EMPLOYEE.fdb";

				String url = "jdbc:firebirdsql:" + serverName + "/" + porta + ":" + database;
				String user = "sysdba";
				String password = "masterkey";
				conexao = DriverManager.getConnection(url, user, password);
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
		return conexao;
	}
	/*
	 * public int GetId() throws SQLException { int codigo = 0; String sql =
	 * "SELECT CUST_NO, CUSTOMER FROM CUSTOMER"; PreparedStatement ps =
	 * ConexaoDatabase.conexao.prepareStatement(sql);
	 * 
	 * ResultSet rs = ps.executeQuery();
	 * 
	 * while (rs.next()) { codigo = rs.getInt("CUST_NO");
	 * 
	 * String nome = rs.getString("CUSTOMER"); System.out.println("Código: " +
	 * codigo + " Nome: " + nome); }
	 * 
	 * return codigo; }
	 */
}
