using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.RegularExpressions;
using System.Web;

namespace Nerddinner.Models
{
    public partial class Dinner
    {
        public bool IsValid()
        {
            {return (GetRuleViolations().Count()==0);}
        }
        public IEnumerable<RuleViolation> GetRuleViolations()
        {
            if (string.IsNullOrEmpty(Title))
                yield return new RuleViolation("Title required", "Title");

            if (string.IsNullOrEmpty(HostBy))
                yield return new RuleViolation("Hostedby required", "Hostby");

            if (string.IsNullOrEmpty(Adress))
                yield return new RuleViolation("Address required", "Adress");

            if (string.IsNullOrEmpty(Country))
                yield return new RuleViolation("Country required", "Country");

            if (string.IsNullOrEmpty(ContactPhone))
                yield return new RuleViolation("Phone# required", "ContactPhone");

           // if (!PhoneValidator.IsValidNumber(ContactPhone, Country))
                //yield return new RuleViolation("Phone# does not match country", "ContactPhone");
        }
        partial void OnValidate(System.Data.Linq.ChangeAction action)
        {
            if(!IsValid())
                throw new ApplicationException("Rule violations prevent saving");
        }
    }

    public class RuleViolation
    {
        public string ErrorMessage { get; private set; }
        public string PropertyName { get; private set; }

        public RuleViolation(string errorMessage)
        {
            ErrorMessage = errorMessage;
        }

        public RuleViolation(string errorMessage, string propertyName)
        {
            ErrorMessage = errorMessage;
            PropertyName = propertyName;
        }

    }
    
    public class PhoneValidator
    {
        static IDictionary<string, Regex> countryRegex = new Dictionary<string, Regex>()
        {
            {"USA", new Regex("^[2-9] \\d{2} - \\d{3}-\\d{4} $")},
            {"UK",new Regex("(^1300\\d{6}$)|(^1800|1900|1902\\d{6}$)|(^0[2|3|7|8]{1}[0-9]{8}$)|(^13\\d{4}$)|(^04\\d{2,3}\\d{6}$)")},
            {"Netherlands",new Regex("(^\\+[0-9]{2} | ^\\+[0-9]{2}\\(0\\) | ^\\(\\+[0-9]{2}\\) \\(0\\) | ^00[0-9]{2} |^0)([0-9]{9}$ |[0-9\\-\\s]{10}$)")},
       };

        public static bool IsValidNumber(string phoneNumber,string country)
        {
            if (country != null && countryRegex.ContainsKey(country))
                return countryRegex[country].IsMatch(phoneNumber);
            else
                return false;
        }

        public static IEnumerable<string> Countries
        {
            get { return countryRegex.Keys; }
        }

    }

}