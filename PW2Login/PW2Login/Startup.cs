using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Hosting;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.AspNetCore.Session;
using Microsoft.AspNetCore.Http;
using PW2Login.Models;
using PW2Login.Views.Utils;

namespace PW2Login
{
    public class Startup
    {
        public Startup(IConfiguration configuration)
        {
            Configuration = configuration;
        }

        public IConfiguration Configuration { get; }

        // This method gets called by the runtime. Use this method to add services to the container.
        public void ConfigureServices(IServiceCollection services)
        {
            services.AddMvc();

            services.AddDistributedMemoryCache();

            services.AddSession(options =>
            {
                options.Cookie.HttpOnly = true;
                options.Cookie.Name = ".PW2Login.Session";
                options.Cookie.IsEssential = true;

                options.IdleTimeout = TimeSpan.FromMinutes(10);
            });
        }


        // This method gets called by the runtime. Use this method to configure the HTTP request pipeline.
        public void Configure(IApplicationBuilder app, IHostingEnvironment env)
        {
            if (env.IsDevelopment())
            {
                app.UseBrowserLink();
                app.UseDeveloperExceptionPage();
            }
            else
            {
                app.UseExceptionHandler("/Home/Error");
            }

            app.UseStaticFiles();

            app.UseSession();

            app.UseMvc(routes =>
            {
                routes.MapRoute(
                    name: "default",
                    template: "{controller=Home}/{action=Index}/{id?}");
            });
            app.Use(async (context, next) =>
            {
                context.Session.SetString("Logged", "false");
                await next();
            });
            app.Run(async (context) =>
            {
                var logged = context.Session.GetString("Logged");
                await context.Response.WriteAsync($"{logged}");
            });

            app.Use(async (context, next) =>
            {
                context.Session.SetObject("currentuser",
                    new AcessoModel { Usuario = "james", Senha = "senha123" });
                await next();
            });
            app.Run(async (context) =>
            {
                var user = context.Session.GetObject<AcessoModel>("currentuser");
                await context.Response.WriteAsync($"{user.Usuario}, {user.Senha}");
            });

        }
    }
}
