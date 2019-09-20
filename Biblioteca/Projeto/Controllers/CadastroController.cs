using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;

namespace Projeto.Controllers
{
    public class CadastroController : Controller
    {
        public IActionResult CadastroUsuario()
        {
            return View();
        }
    }
}