USE [AtCor]
GO

/****** Object:  StoredProcedure [dbo].[UpdateMeasurementDetails]    Script Date: 07/22/2011 10:48:25 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO


ALTER PROCEDURE [dbo].[UpdateMeasurementDetails]
(
	@systemIdentifier int,
	@groupIdentifier int,
	@PatientNumberInternal int,
	@studyDateTime datetime,	
	@notes nvarchar(MAX),
	@SP smallint,
	@DP smallint,
	@MP smallint,
	@operator nvarchar(25),
	@pwvDistance smallint,
	@pwvDistanceMethod smallint,
	@carotid smallint,
	@femoraltoCuff smallint,
	@cuff smallint,
	@simulation	bit,	
	@bloodPressureRange nvarchar(25),
	@bloodPressureEntryOption smallint,
	@normalRange varbinary(300),
	@referenceRange	varbinary(300),
	@age smallint,
	@isStandardDeviationValid bit,	
	@isFemoralSignalValid bit,	
	@isCarotidSignalValid	bit,	
	@direct	smallint,
	@captureTime smallint,
	@meanCorrectedTime	float,
	@meanDeltaTime	float,
	@meanHeartRate	float,
	@meanPulseWaveVelocity	float,
	@sampleRate	smallint,
	@standardDeviation	float,
	@weightInKilograms	smallint,
	@weightInPounds	smallint,
	@heightInCentimetres smallint,
	@heightInInches	smallint,
	@bodyMassIndex	float,
	@carotidSignalFloatOnSets varbinary(300),
	@carotidSignalOnSetsLength	smallint,
	@carotidSignalPulseHeight float,
	@carotidSignalPulseHeightVariation	float,
	@carotidSignal	varbinary(MAX),
	@carotidSignalLength smallint,
	@correctionTime	float,
	@dataRevision smallint,
	@femoralSignalFloatOnSets varbinary(300),
	@femoralSignalOnSetsLength	smallint,
	@femoralSignalPulseHeight float,
	@femoralSignal varbinary(MAX),
	@femoralSignalLength smallint,
	@numberOfDeltas	smallint,
	@numberOfValidDeltas smallint,
	@returnStudyDatetime datetime output
	
)
AS
BEGIN

	DECLARE @measurementDetailsdatetime datetime2(0)
	BEGIN TRY
	BEGIN TRAN AddMeasurementData
	
	SET @measurementDetailsdatetime = Getdate()
	
	--update measurement details
	
	update dbo.PWVMeasurement set  
	SystemIdentifier = 	@systemIdentifier,
	GroupIdentifier = @groupIdentifier,
	PatientNumberInternal = @PatientNumberInternal,
	--StudyDateTime = @measurementDetailsdatetime,	
	StudyDateTime = @studyDateTime,
	Notes = @notes,
	SP =@SP,
	DP = @DP,
	MP = @MP,
	Operator = @operator,
	PWVDistance = @pwvDistance,
	PWVDistanceMethod = @pwvDistanceMethod,
	Carotid = @carotid,
	FemoraltoCuff = @femoraltoCuff,
	Cuff = @cuff,
	Simulation = @simulation,
	BloodPressureRange = @bloodPressureRange,
	BloodPressureEntryOption = @bloodPressureEntryOption,
	NormalRange = @normalRange,
	ReferenceRange = @referenceRange,
	Age = @age,
	IsStandardDeviationValid = @isStandardDeviationValid,
	IsFemoralSignalValid = @isFemoralSignalValid,
	IsCarotidSignalValid = @isCarotidSignalValid,
	Direct = @direct,
	CaptureTime = @captureTime,
	MeanCorrectedTime = @meanCorrectedTime,
	MeanDeltaTime = @meanDeltaTime,
	MeanHeartRate = @meanHeartRate,
	MeanPulseWaveVelocity = @meanPulseWaveVelocity,
	SampleRate = @sampleRate,
	StandardDeviation = @standardDeviation,
	WeightInKilograms = @weightInKilograms,
	WeightInPounds = @weightInPounds,
	HeightInCentimetres = @heightInCentimetres,
	HeightInInches = @heightInInches,
	BodyMassIndex = @bodyMassIndex,
	CarotidSignalFloatOnSets = @carotidSignalFloatOnSets,
	CarotidSignalOnSetsLength = @carotidSignalOnSetsLength,
	CarotidSignalPulseHeight = @carotidSignalPulseHeight,
	CarotidSignalPulseHeightVariation = @carotidSignalPulseHeightVariation,
	CarotidSignal = @carotidSignal,
	CarotidSignalLength = @carotidSignalLength,
	CorrectionTime = @correctionTime,
	DataRevision = @dataRevision,
	FemoralSignalFloatOnSets = @femoralSignalFloatOnSets,
	FemoralSignalOnSetsLength = @femoralSignalOnSetsLength,
	FemoralSignalPulseHeight = @femoralSignalPulseHeight,
	FemoralSignal = @femoralSignal,
	FemoralSignalLength = @femoralSignalLength,
	NumberOfDeltas = @numberOfDeltas,
	NumberOfValidDeltas = @numberOfValidDeltas
	where  studydatetime = convert(varchar(100), @studyDateTime, 120)  and PatientNumberInternal  = @PatientNumberInternal and GroupIdentifier = @groupIdentifier and SystemIdentifier = @systemIdentifier
	
	set @returnStudyDatetime = @measurementDetailsdatetime
	COMMIT TRAN AddMeasurementData
	END TRY
	BEGIN CATCH
		ROLLBACK TRAN AddMeasurementData
	END CATCH
	

END


GO

