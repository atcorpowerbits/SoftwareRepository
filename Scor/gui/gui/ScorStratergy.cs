/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
     Filename     :     System Key
        
     Author       :     Nitesh Chhedda 
 
     Description  :     This class defines an interface wherein diferent methods are declared which need to implemented for other modes.
*/

/**
 * @namespace AtCor.Scor.Gui.Presentation
 * @brief This namespace implements Presentation related classes.
 * 
 */
namespace AtCor.Scor.Gui.Presentation
{
    /**
   * @class IScorStrategy
   * @brief IScorStrategy is an inteface wherein different methods for different modes are declared.    
   */

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

        void FillSession();      

        void SetHeightWeightUnits();

        void SetDistanceMethodAndUnits();

        void SetBloodPressure();

        bool StartCapture();

        bool StopCapture();

        void ActionPerformedAfterClickingCancel();

        void CalculateReportAfterSuccessfulCapture();

        void SaveCapturedData();

        void InitialiseCaptureScreen();

        void HandleKeyDownEventOnCaptureScreen(System.Windows.Forms.KeyEventArgs e);        

        // void AppendCaptureData();       
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
