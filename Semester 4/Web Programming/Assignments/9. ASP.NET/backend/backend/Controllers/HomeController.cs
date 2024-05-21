using backend.Data_Abstraction_Layer;
using backend.Models;
using Microsoft.AspNetCore.Mvc;
using System.Diagnostics;

namespace backend.Controllers
{
    public class HomeController : Controller
    {
        private readonly ILogger<HomeController> _logger;

        public HomeController(ILogger<HomeController> logger)
        {
            _logger = logger;
        }

        [HttpGet("/users")]
        public IActionResult GetUsers(string role, string name)
        {
            DataAbstractionLayer dal = new DataAbstractionLayer();
            List<User> users = dal.GetUsers();
            List<User> filteredUsers = new List<User>();
            if (string.IsNullOrEmpty(role) && string.IsNullOrEmpty(name))
            {
                return Ok(users);
            }
            foreach (User user in users)
            {
                bool roleMatches = string.IsNullOrEmpty(role) || user.role.Contains(role, StringComparison.OrdinalIgnoreCase);
                bool nameMatches = string.IsNullOrEmpty(name) || user.name.Contains(name, StringComparison.OrdinalIgnoreCase);

                if (roleMatches && nameMatches)
                {
                    filteredUsers.Add(user);
                }
            }
            return Ok(filteredUsers);
        }

        [HttpGet("/user")]
        public IActionResult GetUser(int userID)
        {
            DataAbstractionLayer dal = new DataAbstractionLayer();
            List<User> users = dal.GetUsers();
            User user = users.Find(u => u.userID == userID);
            return Ok(user);
        }

        [HttpPost("/add")]
        public IActionResult AddUser(User user)
        {
            DataAbstractionLayer dal = new DataAbstractionLayer();
            dal.addUser(user);
            return Ok();
        }

        [HttpDelete("/delete")]
        public IActionResult DeleteUser(int userID)
        {
            DataAbstractionLayer dal = new DataAbstractionLayer();
            dal.deleteUser(userID);
            return Ok();
        }

        [HttpPut("/update")]
        public IActionResult UpdateUser(User user)
        {
            DataAbstractionLayer dal = new DataAbstractionLayer();
            dal.updateUser(user);
            return Ok();
        }

        [HttpPost("/login")]
        public IActionResult Login(string username, string password)
        {
            DataAbstractionLayer dal = new DataAbstractionLayer();
            List<User> users = dal.GetUsers();
            User user = users.Find(u => u.username == username && u.password == password);
            if (user == null)
            {
                return Unauthorized();
            }
            return Ok(user);
        }

        public IActionResult Index()
        {
            return View();
        }

        public IActionResult Privacy()
        {
            return View();
        }

        [ResponseCache(Duration = 0, Location = ResponseCacheLocation.None, NoStore = true)]
        public IActionResult Error()
        {
            return View(new ErrorViewModel { RequestId = Activity.Current?.Id ?? HttpContext.TraceIdentifier });
        }
    }
}
