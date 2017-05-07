using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using Nerddinner.Models;

namespace Nerddinner.Controllers
{
    public class DinnersController : Controller
    {

        DinnerRepository dinnerRepository = new DinnerRepository();

 
        //
        // GET: /Dinners/

  /*      public ActionResult Index()
        {
            var dinners = dinnerRepository.FindUpcomingDinners();
            var paginatedDinner = dinners.Skip(0).Take(5).ToList();
            var numberofallDinners = dinnerRepository.FindAllDinners().Count();
            if (numberofallDinners > 5) { numberofallDinners = 5; }

            return View((new DinnerViewModel{Dinners=paginatedDinner,NumberofallDinners=numberofallDinners}));
        }
*/
        //
        // GET: /Dinners/Page/2
        public ActionResult Index(int? page)
        {
            const int pagesize = 5;
            var dinners = dinnerRepository.FindUpcomingDinners();
            var numskip = (page ?? 0) * pagesize;
            //var paginatedDinner = dinners.Skip(numskip).Take(pagesize).ToList();
            var paginatedDinner = new PaginatedList<Dinner>(dinners,page??0,pagesize);
            var numberofallDinners = dinnerRepository.FindAllDinners().Count()-numskip;
            if (numberofallDinners > pagesize) { numberofallDinners = pagesize; }
            return View(new DinnerViewModel{Dinners=paginatedDinner,NumberofallDinners=numberofallDinners});
        }
       
        //
        // GET: /Dinners/Details/2
       
        public ActionResult Details(int id)
        {
            Dinner dinner = dinnerRepository.GetDinner(id);

            if (dinner == null)
                return View("NotFound");
            else
                return View( dinner);

        }

        //
        // GET: /Dinners/Edit/2
        public ActionResult Edit(int id)
        {
            Dinner dinner = dinnerRepository.GetDinner(id);
            ViewData["Countries"] = new SelectList(PhoneValidator.Countries, dinner.Country);
            return View(dinner);
        }
        //
        // POST: /Dinners/Edit/2
        [AcceptVerbs(HttpVerbs.Post)]
        public ActionResult Edit(int id, FormCollection formValues)
        {
            //Retrieve existing dinner
            Dinner dinner = dinnerRepository.GetDinner(id);

            //Update dinner with form posted values
            try
            {
                UpdateModel(dinner);
                dinnerRepository.save();
                return RedirectToAction("Details", new { id = dinner.DinnerID });
            }
            catch
            {
                foreach (var issue in dinner.GetRuleViolations())
                {
                    ModelState.AddModelError(issue.PropertyName,issue.ErrorMessage);
                    ViewData["Countries"] = new SelectList(PhoneValidator.Countries, dinner.Country);
                 
                }
            }

            //Perform HTTp redirect to details page for the saved Dinner
            return View(dinner);
        }

        //
        //GET : /Dinners/Create
        [Authorize]
        public ActionResult Create()
        {
            Dinner dinner = new Dinner()
            {
                EventDate = DateTime.Now.AddDays(7)
            };
            return View(dinner);
        }

        //
        //POST :/Dinners/Create
        [AcceptVerbs(HttpVerbs.Post),Authorize]
        public ActionResult Create(FormCollection formValues)
        {
            Dinner dinner = new Dinner();

            try
            {
                UpdateModel(dinner);

                dinnerRepository.Add(dinner);
                dinnerRepository.save();

                return RedirectToAction("Details", new { id = dinner.DinnerID });
            }
            catch
            {
                foreach (var issue in dinner.GetRuleViolations())
                {
                    ModelState.AddModelError(issue.PropertyName,issue.ErrorMessage);
                }
            }
             return View(dinner);
        }

        //
        //GET: /Dinners/Delete/1
        public ActionResult Delete(int id)
        {
            Dinner dinner = dinnerRepository.GetDinner(id);

            if(dinner == null)
            {
                return View("NotFound");
            }
            else
            {
                return View(dinner);
            }
        }

        //
        //POST: /Dinners/Delete/1
        [AcceptVerbs(HttpVerbs.Post)]
        public ActionResult Delete(int id, string confirmButton)
        {
            Dinner dinner = dinnerRepository.GetDinner(id);
            if (dinner == null)
                return View("NotFound");

            dinnerRepository.Delete(dinner);
            dinnerRepository.save();

            return View("Deleted");
        }


    }
}

public class DinnerViewModel    
{
    public PaginatedList<Dinner> Dinners  { get; set; }
    public int NumberofallDinners { get; set; }
}

public class PaginatedList<T> : List<T>
{
    public int PageIndex { get; private set; }
    public int PageSize { get; private set; }
    public int TotalCount { get; private set; }
    public int TotalPages { get; private set; }

    public PaginatedList(IQueryable<T> source, int pageIndex, int pageSize)
    {
        PageIndex = pageIndex;
        PageSize = pageSize;
        TotalCount = source.Count();
        TotalPages = (int)Math.Ceiling(TotalCount / (double)PageSize);

        this.AddRange(source.Skip(PageIndex * PageSize).Take(PageSize));
    }

    public bool HasPreviousPage
    {
        get { return (PageIndex > 0); }
    }
    public bool HasNextPage
    {
        get { return (PageIndex + 1 < TotalPages); }
    }
}