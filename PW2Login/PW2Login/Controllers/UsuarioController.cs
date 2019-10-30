using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using PW2Login.Models;

namespace PW2Login.Controllers
{
    public class UsuarioController : Controller
    {

        static List<UsuarioModel> listaUsuario = new List<UsuarioModel>();
        public ActionResult Consultar()
        {
            if (listaUsuario.Count == 0)
                listaUsuario = new UsuarioModel().GetListaUsuario();
            return View(listaUsuario);
        }

        // GET: Usuario
        public ActionResult Index()
        {
            return View();
        }

        // GET: Usuario/Details/5
        public ActionResult Detalhar(UsuarioModel usuario)
        {
            return View(usuario);
        }

        // GET: Usuario/Create
        public ActionResult Cadastrar()
        {
            int id = listaUsuario.Last().Id + 1;
            return View(new UsuarioModel(id));
        }

        // POST: Usuario/Create
        [HttpPost]
        [ValidateAntiForgeryToken]
        public ActionResult Cadastrar(UsuarioModel usuario)
        {
            try
            {
                // TODO: Add insert logic here
                listaUsuario.Add(usuario);

                return RedirectToAction("Consultar", "Usuario");
            }
            catch
            {
                return View();
            }
        }

        // GET: Usuario/Edit/5
        public ActionResult Edit(int id)
        {
            return View();
        }

        // POST: Usuario/Edit/5
        [HttpPost]
        [ValidateAntiForgeryToken]
        public ActionResult Editar(UsuarioModel usuario)
        {
            try
            {
                // TODO: Add update logic here
                UsuarioModel novoUsuario = listaUsuario.FirstOrDefault(user => user.Id == usuario.Id);
                novoUsuario.Nome = usuario.Nome;
                novoUsuario.Sobrenome = usuario.Sobrenome;
                novoUsuario.DataNascimento = usuario.DataNascimento;
                novoUsuario.Email = usuario.Email;

                return RedirectToAction("Consultar", "Usuario");

            }
            catch
            {
                return View();
            }
        }

        // GET: Usuario/Delete/5
        public ActionResult Delete(int id)
        {
            UsuarioModel usuario = listaUsuario.FirstOrDefault(user => user.Id == id);
            return View(usuario);
        }

        // POST: Usuario/Delete/5
        [HttpPost]
        [ValidateAntiForgeryToken]
        public ActionResult Deletar(UsuarioModel usuario)
        {
            try
            {
                // TODO: Add delete logic here
                UsuarioModel deletarUsuario = listaUsuario.FirstOrDefault(user => user.Id == usuario.Id);
                listaUsuario.Remove(deletarUsuario);
                return RedirectToAction("Consultar", "Usuario");
            }
            catch
            {
                return View();
            }
        }
    }
}