using System.Threading.Tasks;
using Horizon.Server.Models;

namespace Horizon.Server.Interfaces
{
    public interface IAPIHelper
    {
        Task<AuthenticatedUser> Authenticate(string username, string password);
    }
}