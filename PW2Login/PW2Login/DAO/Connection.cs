using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using MySql.Data.MySqlClient;
using System.Data;
namespace PW2Login.DAO
{
    public class Connection
    {
        public void Conexao()
        {
            try
            {
                MySqlConnection Con = new MySqlConnection("server = localhost; userid = root; database = Cadastro; password =");
                Con.Open();
                if (Con.State == ConnectionState.Open){
                    Con.Close();
                }
            }
            catch(MySqlException Ex)
            {

            }

        }
    }

}
