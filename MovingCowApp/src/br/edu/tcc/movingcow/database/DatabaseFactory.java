package br.edu.tcc.movingcow.database;

import br.edu.tcc.movingcow.database.enumeradores.TipoDatabase;
import br.edu.tcc.movingcow.database.interfaces.ConexaoDatabase;

public class DatabaseFactory {
	
	public static ConexaoDatabase getConexaoDatabase(TipoDatabase tipoDatabase) {			
		
		if (tipoDatabase == TipoDatabase.tdFirebird){
			return new ConexaoFirebird();		
		}
		
		return null;
	}

}