using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using AtCor.Scor.BusinessLogic;

namespace AtCor.Scor.Gui.Presentation
{
    public interface IScorStrategy
    {
        // Creating a property for bizobject.
        // string BizObject
        // {
        //    get;
        // }

        // List down all the methods where in we are calling 
        // the bussiness logic methods.
        void DispatchCaptureData();

        void LoadReport();

        // bool StartCapture();
        // void StopCapture();
        // void AppendCaptureData();
        // void SaveCapturedData();
        // void CalculateReport();
        // void CalculateAge();
        // void Populate(crxPwv);
        // bool Validate();
        // void RecalculatePWVReport(crxPwv);
        // void GetBpRefRange();
        // bool Initialise();
        // void ValidateAgeLimit();
    }
}
