using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using PW2Login.Models;

namespace PW2Login.Controllers
{
    [Produces("application/json")]
    [Route("api/AutenticacaoAPI")]
    public class AutenticacaoAPIController : Controller
    {
        // GET: api/AutenticacaoAPI
        [HttpGet]
        public IEnumerable<string> Get()
        {
            return new string[] { "value1", "value2" };
        }

        // GET: api/AutenticacaoAPI/5
        [HttpGet("{usuario}/{senha}")]
        public string Get(string usuario, string senha)
        {
            AcessoModel acesso = new AcessoModel();
            acesso.Usuario = usuario;
            acesso.Senha = senha;

            if (ValidaLogin(acesso))
                return "Usuário logado via POST";
            else
                return "Usuario não Logado via POST";
            
        }

        public bool ValidaLogin(AcessoModel acesso)
        {
            bool logado = false;
            if ((acesso.Usuario == "admin") && (acesso.Senha == "senha123"))
                logado = true;
            return logado;
        }

        // POST: api/AutenticacaoAPI
        [HttpPost]
        public string Post([FromBody]AcessoModel acesso)
        {
                if (ValidaLogin(acesso))
                    return "Usuario logado via Post";
                else
                    return "Usuario não logado via Post";
        }
        // PUT: api/AutenticacaoAPI/5
        [HttpPutAttribute("{id}")]
        public void Put(int id, [FromBody]string value)
        {
        }
        
        // DELETE: api/ApiWithActions/5
       [HttpDelete("{id}")]
        public void Delete(int id)
        {
        }
        
    }
}