using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
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
        public IActionResult Longin(AcessoModel acesso)
        {
            AutenticacaoAPIController autenticacaoAPI = new AutenticacaoAPIController();
            if (autenticacaoAPI.ValidaLogin(acesso))
                return RedirectToAction("Index", "Home");
            else
                return RedirectToAction("Login", "Acesso");
        }

        public IActionResult Logout()
        {
            return View();
        }

    }
}