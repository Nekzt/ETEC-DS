using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using PW2Login.Models;

namespace PW2Login.Controllers
{
    public class AcessoController : Controller
    {
        public IActionResult Login()
        {
            return View();

        }
        public IActionResult Logging(AcessoModel acesso)
        {
            AutenticacaoAPIController autenticacaoAPI = new AutenticacaoAPIController();
            if (autenticacaoAPI.ValidaLogin(acesso))
            {
                HttpContext.Session.SetString("Logged", "true");
                return RedirectToAction("Index", "Home");
            }
            else
            {
                return RedirectToAction("Login", "Acesso");
            }
        }
        public IActionResult Logout()
        {
            HttpContext.Session.SetString("Logged", "false");
            return View();
        }

    }
}