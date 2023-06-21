#nullable disable
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
using PP_CRM.Models;

namespace PP_CRM.Data
{
    public class PP_CRMContext : DbContext
    {
        public PP_CRMContext (DbContextOptions<PP_CRMContext> options)
            : base(options)
        {
        }

        public DbSet<PP_CRM.Models.User> User { get; set; }
    }
}
