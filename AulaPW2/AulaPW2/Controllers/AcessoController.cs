using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using AulaPW2.Models;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;

namespace AulaPW2.Controllers
{
    [Produces("application/json")]
    [Route("api/Acesso")]
    public class AcessoController : Controller
    {
        // GET: api/Acesso
        [HttpGet("{usuario}/{senha}")]
        public string Get(string usuario, string senha)
        {
            AcessoModel acesso = new AcessoModel();
            acesso.Usuario = usuario;
            acesso.Senha = senha;

            if (ValidaLogin(acesso))
            {
                return "Usuário logado";
            }
            else
            {
                return "Usuário não-logado";
            }
        }
        [HttpPost]
        public string Post([FromBody]AcessoModel acesso)
        {
            if (ValidaLogin(acesso))
            {
                return "Usuário logado POST";
            }
            else
            {
                return "Usuário não-logado POST";
            }
        }
        public bool ValidaLogin(AcessoModel acesso)
        {
            if (acesso.Usuario == "admin" && acesso.Senha == "potatinho123")
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
}
