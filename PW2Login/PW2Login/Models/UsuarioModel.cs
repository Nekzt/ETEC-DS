using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace PW2Login.Models
{
    public class UsuarioModel
    {
        public int Id{ get; set;}
        public string Nome { get; set; }
        public string Sobrenome { get; set; }
        public DateTime DataNascimento { get; set; }
        public string Email { get; set; }
        public AcessoModel Acesso { get; set; }

        public UsuarioModel()
        {

        }
        public UsuarioModel(int id)
        {
            Id = id;
        }
        public UsuarioModel(int id, string nome, string sobrenome, DateTime dataNascimento, string email, AcessoModel acesso)
        {
            Id = id;
            Nome = nome;
            Sobrenome = sobrenome;
            DataNascimento = dataNascimento;
            Email = email;
            Acesso = acesso;
        }

        public List<UsuarioModel> GetListaUsuario()
        {
            List<UsuarioModel> listaUsuarios = new List<UsuarioModel>();
            listaUsuarios.Add(new UsuarioModel(1, "Jeff", "Pedro", new DateTime(1984, 02, 02), "jrsp.sc@gmail.com", new AcessoModel("Jeff", "senha123")));
            listaUsuarios.Add(new UsuarioModel(1, "Mayke", "Sei", new DateTime(1993, 01, 01), "mayke@gmail.com", new AcessoModel("Mayke", "senha123")));
            listaUsuarios.Add(new UsuarioModel(1, "Willian", "Lá", new DateTime(1999, 01, 01), "willian@gmail.com", new AcessoModel("Willian", "senha123")));
            listaUsuarios.Add(new UsuarioModel(1, "Renata", "Nome", new DateTime(1997, 01, 01), "renata@gmail.com", new AcessoModel("Renata", "senha123")));

            return listaUsuarios;
        }

    }
}
