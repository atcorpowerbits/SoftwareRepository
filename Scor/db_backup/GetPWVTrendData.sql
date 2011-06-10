USE [AtCor]
GO

/****** Object:  StoredProcedure [dbo].[GetPWVTrendData]    Script Date: 05/27/2011 10:15:24 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

ALTER procedure [dbo].[GetPWVTrendData]
(
      @systemIdentifier int,
      @groupIdentifier int,
      @PatientNumberInternal int,
      @studyDateTimeArrStr nvarchar(MAX),
      @heartRateArrStr nvarchar(MAX) output,
      @pulseWaveVelocityArrStr nvarchar(MAX) output,
      @StandardDeviationArrStr nvarchar(MAX) output,
      @IsStdDevValidArrStr nvarchar(MAX) output,
      @SpValidArrStr nvarchar(MAX) output,
      @DpValidArrStr nvarchar(MAX) output,
      @MpValidArrStr nvarchar(MAX) output

)
AS
BEGIN

DECLARE @position INT -- holds the location of the separator
DECLARE @tempstudyDateTime VarChar(max)
DECLARE @heartRate nVarChar(max)
DECLARE @PulseWave nVarChar(max)
DECLARE @stdDev nVarChar(max)
DECLARE @isStdDev nVarChar(max)
DECLARE @SpValue nVarChar(max)
DECLARE @DpValue nVarChar(max)
DECLARE @MpValue nVarChar(max)

SET @heartRateArrStr = ''
SET @pulseWaveVelocityArrStr = ''
SET @StandardDeviationArrStr = ''
SET @IsStdDevValidArrStr = ''
SET @SpValidArrStr = ''
SET @DpValidArrStr = ''
SET @MpValidArrStr = ''

      WHILE PATINDEX('%,%' , @studyDateTimeArrStr) <> 0 
      BEGIN
            
            SET @heartRate = ''
            SET @PulseWave = ''
            SET @stdDev = ''
            SET @isStdDev = ''
            SET @SpValue = ''
            SET @DpValue = ''
            SET @MpValue = ''
            
            -- patindex matches the a pattern against a string
            SET @position =  PATINDEX('%,%' , @studyDateTimeArrStr)

            -- The following statement extracts the value FROM the string value
            SET @tempstudyDateTime = LEFT(@studyDateTimeArrStr, @position - 1)
            
            SELECT @heartRate = round([MeanHeartRate],0),
                     @PulseWave = round([MeanPulseWaveVelocity],1),
                     @stdDev = round([StandardDeviation],1),
                     @isStdDev = [IsStandardDeviationValid],
                     @SpValue = [SP],
                     @DpValue = [DP],
                     @MpValue = [MP]

            FROM dbo.PWVMeasurement  WITH(NOLOCK)
             WHERE PatientNumberInternal  =  @PatientNumberInternal  
               AND GroupIdentifier =  + @groupIdentifier  
               AND SystemIdentifier =  + @systemIdentifier 
               AND studydatetime = @tempstudyDateTime
              
            SET @studyDateTimeArrStr = STUFF(@studyDateTimeArrStr, 1, @position, '')
      
            IF @heartRateArrStr = '' 
                  BEGIN
                        SET @heartRateArrStr = @heartRate 
                  END
            ELSE
                  BEGIN
                        IF @heartRate <> ''
                              SET @heartRateArrStr = @heartRateArrStr + ',' + @heartRate 
                  END
                  
            IF @pulseWaveVelocityArrStr = '' 
                  BEGIN
                        SET @pulseWaveVelocityArrStr = @PulseWave
                  END
            ELSE
                  BEGIN
                        IF @PulseWave <> ''
                              SET @pulseWaveVelocityArrStr = @pulseWaveVelocityArrStr + ',' + @PulseWave
                  END   
                  

            IF @StandardDeviationArrStr = '' 
                  BEGIN
                        SET @StandardDeviationArrStr = @stdDev
                  END
            ELSE
                  BEGIN
                        IF @stdDev <> ''
                              SET @StandardDeviationArrStr = @StandardDeviationArrStr + ',' + @stdDev
                  END   
            
            
            IF @IsStdDevValidArrStr = '' 
                  BEGIN
                        SET @IsStdDevValidArrStr = @isStdDev
                  END
            ELSE
                  BEGIN
                        IF @isStdDev <> ''
                              SET @IsStdDevValidArrStr = @IsStdDevValidArrStr + ',' + @isStdDev
                  END
                  
            IF @SpValidArrStr = '' 
                  BEGIN
                        SET @SpValidArrStr = @SpValue
                  END
            ELSE
                  BEGIN
                        IF @SpValue <> ''
                              SET @SpValidArrStr = @SpValidArrStr + ',' + @SpValue
                  END 
                    
            IF @DpValidArrStr = '' 
                  BEGIN
                        SET @DpValidArrStr = @DpValue
                  END
            ELSE
                  BEGIN
                        IF @DpValue <> ''
                              SET @DpValidArrStr = @DpValidArrStr + ',' + @DpValue
                  END
                     
            IF @MpValidArrStr = '' 
                  BEGIN
                        SET @MpValidArrStr = @MpValue
                  END
            ELSE
                  BEGIN
                        IF @MpValue <> ''
                              SET @MpValidArrStr = @MpValidArrStr + ',' + @MpValue
                  END      
      END   
END 

GO

