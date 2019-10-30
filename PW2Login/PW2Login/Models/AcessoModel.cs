using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace PW2Login.Models
{
    public class AcessoModel
    {
        private string v1;
        private string v2;

        public AcessoModel()
        {
        }

        public AcessoModel(string v1, string v2)
        {
            this.v1 = v1;
            this.v2 = v2;
        }

            public string Usuario{get;set;}
            public string Senha{get;set;}
    }
}
