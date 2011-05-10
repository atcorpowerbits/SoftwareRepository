
CREATE DATABASE [AtCor]

GO

USE [AtCor]
GO
/****** Object:  Table [dbo].[Group]    Script Date: 11/24/2010 11:11:58 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[Group](
	[SystemIdentifier] [nvarchar](5) NOT NULL,
	[GroupIdentifier] [int] IDENTITY(1,1) NOT NULL,
	[GroupName] [nvarchar](25) NOT NULL,
	[CharSpare1] [nvarchar](50) NULL,
	[CharSpare2] [nvarchar](50) NULL,
	[IntSpare1] [int] NULL,
	[IntSpare2] [int] NULL,
 CONSTRAINT [PK_Group] PRIMARY KEY CLUSTERED 
(
	[SystemIdentifier] ASC,
	[GroupIdentifier] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
/****** Object:  Table [dbo].[Patient]    Script Date: 11/19/2010 16:30:19 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Patient](
	[SystemIdentifier] [nvarchar](5) NOT NULL,
	[PatientNumberInternal] [int] IDENTITY(1,1) NOT NULL,
	[PatientIDExternalReference] [nvarchar](10) NULL,
	[LastName] [nvarchar](25) NOT NULL,
	[FirstName] [nvarchar](25) NULL,
	[DateOfBirth] [datetime] NOT NULL,
	[Gender] [nvarchar](6) NOT NULL,
	[CharSpare1] [nvarchar](50) NULL,
	[CharSpare2] [nvarchar](50) NULL,
	[IntSpare1] [int] NULL,
	[IntSpare2] [int] NULL,
	[FloatSpare1] [float] NULL,
	[FloatSpare2] [float] NULL,
	[ArraySpare1] [varbinary](300) NULL,
	[ArraySpare2] [varbinary](300) NULL,
 CONSTRAINT [PK_Patient] PRIMARY KEY CLUSTERED 
(
	[SystemIdentifier] ASC,
	[PatientNumberInternal] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[PWVMeasurement]    Script Date: 11/19/2010 16:30:19 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[PWVMeasurement](
	[SystemIdentifier] [nvarchar](5) NOT NULL,
	[GroupIdentifier] [int] NOT NULL,
	[PatientNumberInternal] [int] NOT NULL,
	[StudyDateTime] [datetime] NOT NULL,
	[Notes] [nvarchar](max) NULL,
	[SP] [smallint] NULL,
	[DP] [smallint] NULL,
	[MP] [smallint] NULL,
	[Operator] [nvarchar](25) NULL,
	[PWVDistance] [smallint] NOT NULL,
	[PWVDistanceMethod] [smallint] NULL,
	[Carotid] [smallint] NULL,
	[FemoraltoCuff] [smallint] NULL,
	[Cuff] [smallint] NULL,
	[Simulation] [bit] NULL,
	[BloodPressureRange] [nvarchar](25) NULL,
	[BloodPressureEntryOption] [smallint] NULL,
	[NormalRange] [varbinary](300) NULL,
	[ReferenceRange] [varbinary](300) NULL,
	[Age] [smallint] NULL,
	[IsStandardDeviationValid] [bit] NULL,
	[IsFemoralSignalValid] [bit] NULL,
	[IsCarotidSignalValid] [bit] NULL,
	[Direct] [smallint] NULL,
	[CaptureTime] [smallint] NULL,
	[MeanCorrectedTime] [float] NULL,
	[MeanDeltaTime] [float] NULL,
	[MeanHeartRate] [float] NULL,
	[MeanPulseWaveVelocity] [float] NULL,
	[SampleRate] [smallint] NULL,
	[StandardDeviation] [float] NULL,
	[WeightInKilograms] [smallint] NULL,
	[WeightInPounds] [smallint] NULL,
	[HeightInCentimetres] [smallint] NULL,
	[HeightInInches] [smallint] NULL,
	[BodyMassIndex] [float] NULL,
	[CarotidSignalFloatOnSets] [varbinary](300) NULL,
	[CarotidSignalOnSetsLength] [smallint] NULL,
	[CarotidSignalPulseHeight] [float] NULL,
	[CarotidSignalPulseHeightVariation] [float] NULL,
	[CarotidSignal] [varbinary](max) NULL,
	[CarotidSignalLength] [smallint] NULL,
	[CorrectionTime] [float] NULL,
	[DataRevision] [smallint] NULL,
	[FemoralSignalFloatOnSets] [varbinary](300) NULL,
	[FemoralSignalOnSetsLength] [smallint] NULL,
	[FemoralSignalPulseHeight] [float] NULL,
	[FemoralSignal] [varbinary](max) NULL,
	[FemoralSignalLength] [smallint] NULL,
	[NumberOfDeltas] [smallint] NULL,
	[NumberOfValidDeltas] [smallint] NULL,
	[CharSpare1] [nvarchar](50) NULL,
	[CharSpare2] [nvarchar](50) NULL,
	[IntSpare1] [int] NULL,
	[IntSpare2] [int] NULL,
	[FloatSpare1] [float] NULL,
	[FloatSpare2] [float] NULL,
	[ArraySpare1] [varbinary](300) NULL,
	[ArraySpare2] [varbinary](300) NULL,
 CONSTRAINT [PK_PWVMeasurement] PRIMARY KEY CLUSTERED 
(
	[SystemIdentifier] ASC,
	[GroupIdentifier] ASC,
	[PatientNumberInternal] ASC,
	[StudyDateTime] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[PatientGroupRelation]    Script Date: 11/24/2010 11:14:21 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[PatientGroupRelation](
	[SystemIdentifier] [nvarchar](5) NOT NULL,
	[GroupIdentifier] [int] NOT NULL,
	[PatientNumberInternal] [int] NOT NULL,
	[PatientGroupTimeStamp] [timestamp] NOT NULL,
	[CharSpare1] [nvarchar](50) NULL,
	[CharSpare2] [nvarchar](50) NULL,
	[IntSpare1] [int] NULL,
	[IntSpare2] [int] NULL,
 CONSTRAINT [PK_PatientGroupRelation] PRIMARY KEY CLUSTERED 
(
	[SystemIdentifier] ASC,
	[GroupIdentifier] ASC,
	[PatientNumberInternal] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
/****** Object:  StoredProcedure [dbo].[CheckPatientIDExist]    Script Date: 11/24/2010 11:21:39 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO


--This procedure checks if patient external reference ID exists or not
--if exists it returns 1 else 0

CREATE PROCEDURE [dbo].[CheckPatientIDExist]
(
	@systemIdentifier int,
	@patientIdExtRef nvarchar(10)
)
AS
BEGIN

	IF EXISTS(SELECT 'x' FROM dbo.Patient WHERE SystemIdentifier = @systemIdentifier and PatientIDExternalReference = @patientIdExtRef)
		SELECT 1
	ELSE
		SELECT 0
END



GO

/****** Object:  StoredProcedure [dbo].[CheckGroupNameExist]    Script Date: 11/24/2010 11:19:03 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO


--This procedure checks if patient external reference ID exists or not
--if exists it returns 1 else 0

CREATE PROCEDURE [dbo].[CheckGroupNameExist]
(
	@systemIdentifier int,
	@groupName nvarchar(25)
)
AS
BEGIN
--
	IF EXISTS(SELECT 'x' FROM dbo.[Group] WHERE SystemIdentifier = @systemIdentifier and GroupName = @groupName)
		SELECT 1
	ELSE
		SELECT 0
END

GO
/****** Object:  StoredProcedure [dbo].[GetGroupList]    Script Date: 11/24/2010 11:24:24 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE procedure [dbo].[GetGroupList]
AS
begin
	
	select GroupIdentifier,GroupName  from dbo.[Group]	order by GroupName

end
GO
/****** Object:  StoredProcedure [dbo].[UpdatePatientDetails]    Script Date: 11/24/2010 11:28:34 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[UpdatePatientDetails]
(
	@systemIdentifier int,
	@PatientNumberInternal int,
	@patientIDExternalReference nvarchar(10),
	@LastName nvarchar(25),
	@FirstName nvarchar(25),
	@DateOfBirth datetime,
	@gender nvarchar(6),
	@groupIdentifier int,
	@groupName nvarchar(25),
	@spValidation bit,
	@groupIdentifier_modified int output
	
	
)
AS
BEGIN

declare @groupidentifiernew int

	BEGIN TRY
	BEGIN TRAN UpdatePatient	
	
--update patient
	update dbo.Patient set  
	PatientIDExternalReference = @patientIDExternalReference,
	LastName = @LastName,
	FirstName = @FirstName,
	DateOfBirth = @DateOfBirth,
	Gender = @gender
	where PatientNumberInternal  = @PatientNumberInternal and SystemIdentifier = @systemIdentifier

	

--insert groupname if it does not exists and fetch identity of record inserted or use parameter @groupidentifier for already existing groupname	
	
	if exists(select 'x' from [Group] where SystemIdentifier = @systemIdentifier and GroupName = @groupName)
	begin
		select @groupidentifiernew = groupIdentifier from [Group] where SystemIdentifier = @systemIdentifier and GroupName = @groupName
		
	end
	else 
	begin
		insert into [Group](SystemIdentifier, GroupName) values (@systemIdentifier, @groupName)
		select @groupidentifiernew = scope_identity()
	end
	
	select @groupIdentifier_modified = @groupidentifiernew
--insert entry into dbo.PatientGroupRelation if it does not exists or update if it exists
	if(@spValidation = 1)
	begin
	--modify existing relation	
	update PatientGroupRelation set GroupIdentifier = @groupidentifiernew where SystemIdentifier = @systemIdentifier and GroupIdentifier = @groupIdentifier and PatientNumberInternal = @PatientNumberInternal 
	
	if exists(select 'x' from dbo.PWVMeasurement where SystemIdentifier = @systemIdentifier and GroupIdentifier = @groupIdentifier and PatientNumberInternal = @PatientNumberInternal )
	begin
			update dbo.PWVMeasurement set GroupIdentifier = @groupidentifiernew where SystemIdentifier = @systemIdentifier and GroupIdentifier = @groupIdentifier and PatientNumberInternal = @PatientNumberInternal 
	end
		
	end
	else
	begin
		--enter new relation
		if not exists(select 'x' from PatientGroupRelation where SystemIdentifier = @systemIdentifier and GroupIdentifier = @groupidentifiernew and PatientNumberInternal = @PatientNumberInternal)
		begin
			insert into dbo.PatientGroupRelation(SystemIdentifier, GroupIdentifier, PatientNumberInternal)
			values(@systemIdentifier, @groupidentifiernew, @PatientNumberInternal)
		end
	end
	
	COMMIT TRAN UpdatePatient
	END TRY
	BEGIN CATCH
		ROLLBACK TRAN UpdatePatient
	END CATCH	
	

END


GO

/****** Object:  StoredProcedure [dbo].[DeletePatientDetails]    Script Date: 11/24/2010 11:23:40 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO



CREATE PROCEDURE [dbo].[DeletePatientDetails]
(
	@systemIdentifier int,
	@groupIdentifier int,
	@patientNumberInternal int
)
AS
BEGIN
	
	declare @varnum int
	BEGIN TRY
	BEGIN TRAN DeletePatient
	
	--delete from pwv measurement
	DELETE from dbo.PWVMeasurement WHERE PatientNumberInternal = @patientNumberInternal and SystemIdentifier = @systemIdentifier and GroupIdentifier = @groupIdentifier
	
	-- delete from dbo.PatientGroupRelation
	DELETE FROM PatientGroupRelation WHERE PatientNumberInternal = @patientNumberInternal and SystemIdentifier = @systemIdentifier and GroupIdentifier = @groupIdentifier
	
	SELECT @varnum = COUNT(*) FROM PatientGroupRelation WHERE PatientNumberInternal = @patientNumberInternal and SystemIdentifier = @systemIdentifier

	if @varnum = 0
	begin
		--delete from pwv measurement
		
		--delete from patient table
		DELETE FROM Patient WHERE PatientNumberInternal = @patientNumberInternal and SystemIdentifier = @systemIdentifier

	end		
	
	COMMIT TRAN DeletePatient
	END TRY
	BEGIN CATCH
		ROLLBACK TRAN DeletePatient
	END CATCH
	
	

END


GO
/****** Object:  StoredProcedure [dbo].[CheckPatientRecordExists]    Script Date: 11/24/2010 11:22:37 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[CheckPatientRecordExists]
(
	@systemIdentifier int,
	@patientIDExternalReference	 nvarchar(10),
	@lastName nvarchar(25),
	@firstName nvarchar(25),
	@dateOfBirth datetime,
	@gender nvarchar(6),
	@groupname nvarchar(25)
	
)
AS
BEGIN
	declare @groupid int
	
	--check for 5 fields and 6 fields
	if exists(select 'x' from dbo.Patient where SystemIdentifier = @systemIdentifier and PatientIDExternalReference = @patientIDExternalReference and LastName = @LastName and FirstName = @FirstName and DateOfBirth = @DateOfBirth and Gender = @gender)
	begin
		if exists(SELECT 'x' 
			  FROM dbo.PatientGroupRelation pgr 
			 WHERE pgr.GroupIdentifier IN (SELECT grp.GroupIdentifier 
											 FROM dbo.[Group] grp 
											WHERE grp.GroupName = @groupName)
			   AND pgr.PatientNumberInternal IN (SELECT p.PatientNumberInternal  
												   FROM dbo.Patient	p 
												  WHERE p.LastName = @LastName
													AND p.FirstName = @FirstName
													AND p.PatientIDExternalReference = @patientIDExternalReference
													AND p.DateOfBirth = @DateOfBirth
													AND p.Gender = @gender))
		begin
			select 2
		end													
		else
		begin
			select 1
		end
	
	end
	else
	begin
		select 0
	end
	
	

END

GO
/****** Object:  StoredProcedure [dbo].[InsertPatientDetails]    Script Date: 11/24/2010 11:27:25 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO


CREATE PROCEDURE [dbo].[InsertPatientDetails]
(
	@systemIdentifier int,
	@patientIDExternalReference nvarchar(10),
	@LastName nvarchar(25),
	@FirstName nvarchar(25),
	@DateOfBirth datetime,
	@gender nvarchar(6),
	@groupIdentifier int,
	@groupName nvarchar(25),
	@patientInternalId int output,
	@groupId int output
	
	
)
AS
BEGIN

	declare @patientnumberinternal int, @groupidentifiernew int
	BEGIN TRY
	BEGIN TRAN AddPatient
	
	
--insert into patient
	
		insert into dbo.Patient (SystemIdentifier, PatientIDExternalReference, LastName, FirstName, DateOfBirth, Gender)
		values (@systemIdentifier, @patientIDExternalReference, @LastName, @FirstName, @DateOfBirth, @gender)
		
		set @patientnumberinternal = scope_identity()
		set @patientInternalId = @patientnumberinternal  
			
--fetch identity value of record inserted	
	
	
--insert groupname if it does not exists and fetch identity of record inserted or use parameter @groupidentifier for already existing groupname	
	if exists(select 'x' from [Group] where SystemIdentifier = @systemIdentifier and GroupName = @groupName)
	begin
		
		select @groupidentifiernew = groupIdentifier from [Group] where SystemIdentifier = @systemIdentifier and GroupName = @groupName
		
	end
	else
	begin
		
		insert into [Group](SystemIdentifier, GroupName) values (@systemIdentifier, @groupName)
		select @groupidentifiernew = scope_identity()
	end
	
--insert entry into dbo.PatientGroupRelation	
	insert into dbo.PatientGroupRelation(SystemIdentifier, GroupIdentifier, PatientNumberInternal)
	values(@systemIdentifier,  @groupidentifiernew, @patientnumberinternal)
	
	set @groupId = @groupidentifiernew
	
	
	--select @patientInternalId PatientInternalId,  @groupId GroupIdentifier
	COMMIT TRAN AddPatient
	END TRY
	BEGIN CATCH
		ROLLBACK TRAN AddPatient
	END CATCH
	

END


GO
/****** Object:  StoredProcedure [dbo].[GetPatientDetailsByPatientID]    Script Date: 11/24/2010 11:26:50 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO



CREATE procedure [dbo].[GetPatientDetailsByPatientID]
(
	@systemIdentifier int,
	@patientNumberInternal int,
	@GroupIdentifier int
)
AS
begin
	
	select p.PatientNumberInternal, PatientIDExternalReference, LastName, FirstName, DateOfBirth, Gender, g.GroupName
	from dbo.Patient p join dbo.PatientGroupRelation pg on pg.PatientNumberInternal = p.PatientNumberInternal
	join [Group] g on g.GroupIdentifier = pg.GroupIdentifier
	where p.PatientNumberInternal = @patientNumberInternal and g.GroupIdentifier = @GroupIdentifier and 
	p.SystemIdentifier = @systemIdentifier
	

end
GO

/****** Object:  StoredProcedure [dbo].[GetPatientDetails]    Script Date: 11/24/2010 11:26:00 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO



CREATE procedure [dbo].[GetPatientDetails]
AS
begin
	
	select p.SystemIdentifier, p.PatientNumberInternal, PatientIDExternalReference, LastName, FirstName, CONVERT(datetime, DateOfBirth) DateOfBirth, Gender, g.GroupName, g.GroupIdentifier,PatientGroupTimeStamp
	from dbo.Patient p join dbo.PatientGroupRelation pg on pg.PatientNumberInternal = p.PatientNumberInternal
	join [Group] g on g.GroupIdentifier = pg.GroupIdentifier order by p.PatientNumberInternal,PatientGroupTimeStamp
	
	

end
GO

/****** Object:  StoredProcedure [dbo].[InsertMeasurementDetails]    Script Date: 12/02/2010 16:09:05 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO


/****** Object:  StoredProcedure [dbo].[InsertMeasurementDetails]    Script Date: 12/16/2010 14:48:55 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO


CREATE PROCEDURE [dbo].[InsertMeasurementDetails]
(
	@systemIdentifier int,
	@groupIdentifier int,
	@PatientNumberInternal int,	
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
	@numberOfValidDeltas smallint

	
)
AS
BEGIN

	DECLARE @measurementDetailsdatetime datetime2(0)
	BEGIN TRY
	BEGIN TRAN AddMeasurementData
	
	SET @measurementDetailsdatetime = Getdate()
--insert into PWVMeasurement
	
		insert into dbo.PWVMeasurement (SystemIdentifier,GroupIdentifier,PatientNumberInternal,StudyDateTime,Notes,SP,DP,MP,Operator,PWVDistance,PWVDistanceMethod,Carotid,FemoraltoCuff,Cuff,Simulation,BloodPressureRange,BloodPressureEntryOption,NormalRange,ReferenceRange,Age,IsStandardDeviationValid,IsFemoralSignalValid,IsCarotidSignalValid,Direct,CaptureTime,MeanCorrectedTime,MeanDeltaTime,MeanHeartRate,MeanPulseWaveVelocity,SampleRate,StandardDeviation,WeightInKilograms,WeightInPounds,HeightInCentimetres,HeightInInches,BodyMassIndex,CarotidSignalFloatOnSets,CarotidSignalOnSetsLength,CarotidSignalPulseHeight,CarotidSignalPulseHeightVariation,CarotidSignal,CarotidSignalLength,CorrectionTime,DataRevision,FemoralSignalFloatOnSets,FemoralSignalOnSetsLength,FemoralSignalPulseHeight,FemoralSignal,FemoralSignalLength,NumberOfDeltas,NumberOfValidDeltas)
		values (@systemIdentifier, @groupIdentifier, @PatientNumberInternal, @measurementDetailsdatetime,@Notes,@SP,@DP,@MP,@Operator,@PWVDistance,@PWVDistanceMethod,@Carotid,@FemoraltoCuff,@Cuff,@simulation,@bloodPressureRange,@bloodPressureEntryOption,@normalRange,@referenceRange,@age,@isStandardDeviationValid,@isFemoralSignalValid,@isCarotidSignalValid,@direct,@captureTime,@meanCorrectedTime,@meanDeltaTime,@meanHeartRate,@meanPulseWaveVelocity,@sampleRate,@standardDeviation,@weightInKilograms,@weightInPounds,@heightInCentimetres,@heightInInches,@bodyMassIndex,@carotidSignalFloatOnSets,@carotidSignalOnSetsLength,@carotidSignalPulseHeight,@carotidSignalPulseHeightVariation,@carotidSignal,@carotidSignalLength,@correctionTime,@dataRevision,@femoralSignalFloatOnSets,@femoralSignalOnSetsLength,@femoralSignalPulseHeight,@femoralSignal,@femoralSignalLength,@numberOfDeltas,@numberOfValidDeltas)
		
		
--fetch identity value of record inserted	
	

	COMMIT TRAN AddMeasurementData
	END TRY
	BEGIN CATCH
		ROLLBACK TRAN AddMeasurementData
	END CATCH
	

END


GO


/****** Object:  StoredProcedure [dbo].[UpdateMeasurementDetails]    Script Date: 12/02/2010 16:09:44 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[UpdateMeasurementDetails]
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
	StudyDateTime = @measurementDetailsdatetime,	
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




/****** Object:  StoredProcedure [dbo].[GetMeasurementDetails]    Script Date: 12/16/2010 14:46:08 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE procedure [dbo].[GetMeasurementDetails]
(
	@systemIdentifier int,
	@groupIdentifier int,
	@PatientNumberInternal int,
	@studyDateTime datetime
)
AS
begin
	
	if @studyDateTime is null
	begin
		select [SystemIdentifier], [GroupIdentifier], [PatientNumberInternal], [StudyDateTime],[Notes],[SP], [DP], [MP],[Operator], [PWVDistance],
		[PWVDistanceMethod], [Carotid], [FemoraltoCuff], [Cuff], [Simulation], [BloodPressureRange], [BloodPressureEntryOption], [NormalRange], [ReferenceRange], [Age], [IsStandardDeviationValid],
		[IsFemoralSignalValid], [IsCarotidSignalValid], [Direct], [CaptureTime], [MeanCorrectedTime], [MeanDeltaTime], [MeanHeartRate], [MeanPulseWaveVelocity], [SampleRate], [StandardDeviation], 
		[WeightInKilograms],
	[WeightInPounds],
	[HeightInCentimetres],
	[HeightInInches],
	[BodyMassIndex],
	[CarotidSignalFloatOnSets],
	[CarotidSignalOnSetsLength],
	[CarotidSignalPulseHeight],
	[CarotidSignalPulseHeightVariation] ,
	[CarotidSignal],
	[CarotidSignalLength],
	[CorrectionTime],
	[DataRevision],
	[FemoralSignalFloatOnSets],
	[FemoralSignalOnSetsLength],
	[FemoralSignalPulseHeight],
	[FemoralSignal],
	[FemoralSignalLength],
	[NumberOfDeltas],
	[NumberOfValidDeltas]
	 from dbo.PWVMeasurement where PatientNumberInternal  = @PatientNumberInternal and GroupIdentifier = @groupIdentifier and SystemIdentifier = @systemIdentifier order by StudyDateTime desc
	end
	else
	begin
		select [SystemIdentifier], [GroupIdentifier], [PatientNumberInternal], [StudyDateTime],[Notes],[SP], [DP], [MP],[Operator], [PWVDistance],
		[PWVDistanceMethod], [Carotid], [FemoraltoCuff], [Cuff], [Simulation], [BloodPressureRange], [BloodPressureEntryOption], [NormalRange], [ReferenceRange], [Age], [IsStandardDeviationValid],
		[IsFemoralSignalValid], [IsCarotidSignalValid], [Direct], [CaptureTime], [MeanCorrectedTime], [MeanDeltaTime], [MeanHeartRate], [MeanPulseWaveVelocity], [SampleRate], [StandardDeviation], 
		[WeightInKilograms],
	[WeightInPounds],
	[HeightInCentimetres],
	[HeightInInches],
	[BodyMassIndex],
	[CarotidSignalFloatOnSets],
	[CarotidSignalOnSetsLength],
	[CarotidSignalPulseHeight],
	[CarotidSignalPulseHeightVariation] ,
	[CarotidSignal],
	[CarotidSignalLength],
	[CorrectionTime],
	[DataRevision],
	[FemoralSignalFloatOnSets],
	[FemoralSignalOnSetsLength],
	[FemoralSignalPulseHeight],
	[FemoralSignal],
	[FemoralSignalLength],
	[NumberOfDeltas],
	[NumberOfValidDeltas] from dbo.PWVMeasurement where StudyDateTime = convert( varchar(19),@studyDateTime, 120) and PatientNumberInternal  = @PatientNumberInternal and GroupIdentifier = @groupIdentifier and SystemIdentifier = @systemIdentifier
	end


end

GO

/****** Object:  StoredProcedure [dbo].[BackUpDatabase]    Script Date: 01/07/2011 08:54:18 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[BackUpDatabase]
(
	@FilePath nvarchar(2000)
)
AS
BEGIN	
	
      BACKUP DATABASE  AtCor
      TO DISK = @FilePath  
      WITH INIT,
		
      NAME = 'FULL BACKUP'
		
END

GO

/****** Object:  StoredProcedure [dbo].[MigratePatientDetails]    Script Date: 01/31/2011 18:55:44 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO




CREATE PROCEDURE [dbo].[MigratePatientDetails]
(
	@systemIdentifier int,
	@patientIDExternalReference nvarchar(10),
	@LastName nvarchar(25),
	@FirstName nvarchar(25),
	@DateOfBirth datetime,
	@gender nvarchar(6),
	@groupName nvarchar(25)	
)
AS
BEGIN

	DECLARE @patientnumberinternal int, @groupidentifiernew int, @Count int, @Count2 int, @Count3 int
	
	BEGIN TRY
	BEGIN TRAN AddPatient
	
	-- CHECK WHETHER PATIENT IS PRESENT OR NOT
	if exists(select 'x' from dbo.Patient where SystemIdentifier = @systemIdentifier and PatientIDExternalReference = @patientIDExternalReference and LastName = @LastName and FirstName = @FirstName and DateOfBirth = @DateOfBirth and Gender = @gender)
	begin
		 set @Count = 1
	end
	else
	begin
		set @Count = 0
	end
											
	IF @Count = 1 
	BEGIN 
		--Check group exist
		
		IF EXISTS(SELECT 'x' FROM dbo.[Group] WHERE SystemIdentifier = @systemIdentifier and GroupName = @groupName)
			
			SET  @Count2 = 1
		ELSE
			SET  @Count2 = 0
		--Check relationship with group
		IF @Count2 = 1 
		BEGIN
			SELECT @Count3 = COUNT(1) 
			  FROM dbo.PatientGroupRelation pgr 
			 WHERE pgr.GroupIdentifier IN (SELECT grp.GroupIdentifier 
											 FROM dbo.[Group] grp 
											WHERE grp.GroupName = @groupName)
			   AND pgr.PatientNumberInternal IN (SELECT p.PatientNumberInternal  
												   FROM dbo.Patient	p 
												  WHERE p.LastName = @LastName
													AND p.FirstName = @FirstName
													AND p.PatientIDExternalReference = @patientIDExternalReference
													AND p.DateOfBirth = @DateOfBirth
													AND p.Gender = @gender)
			IF @Count3 = 0 
			BEGIN
				-- insert into relationship table
				
				select @patientnumberinternal = PatientNumberInternal from dbo.Patient where SystemIdentifier = @systemIdentifier and PatientIDExternalReference = @patientIDExternalReference and LastName = @LastName and FirstName = @FirstName and DateOfBirth = @DateOfBirth and Gender = @gender
				
				SELECT @groupidentifiernew = GroupIdentifier  FROM dbo.[Group] WHERE SystemIdentifier = @systemIdentifier and GroupName = @groupName 
				
				insert into dbo.PatientGroupRelation(SystemIdentifier, GroupIdentifier, PatientNumberInternal)
				values(@systemIdentifier,  @groupidentifiernew, @patientnumberinternal)
		
				
			END	
		END												
		ELSE
		BEGIN
			--insert into group and relationship table
			insert into [Group](SystemIdentifier, GroupName) values (@systemIdentifier, @groupName)
			select @groupidentifiernew = scope_identity()
			
			--insert entry into dbo.PatientGroupRelation
			select @patientnumberinternal = PatientNumberInternal from dbo.Patient where SystemIdentifier = @systemIdentifier and PatientIDExternalReference = @patientIDExternalReference and LastName = @LastName and FirstName = @FirstName and DateOfBirth = @DateOfBirth and Gender = @gender
			
			insert into dbo.PatientGroupRelation(SystemIdentifier, GroupIdentifier, PatientNumberInternal)
			values(@systemIdentifier,  @groupidentifiernew, @patientnumberinternal)
	
		END
		
	END
	ELSE	
	BEGIN		--insert into patient
		INSERT INTO dbo.Patient 
				(SystemIdentifier, 
				 PatientIDExternalReference, 
				 LastName, 
				 FirstName, 
				 DateOfBirth, 
				 Gender)
		VALUES (@systemIdentifier, 
				@patientIDExternalReference, 
				@LastName, 
				@FirstName, 
				@DateOfBirth, -- CHANGE TO PATIENT DOB
				@gender)
			
		SET @patientnumberinternal = scope_identity()
	   			
		--fetch identity value of record inserted	
				
		--insert groupname if it does not exists and fetch identity of record inserted or use parameter @groupidentifier for already existing groupname	
		IF EXISTS(SELECT 'x' 
					FROM [Group] 
				   WHERE SystemIdentifier = @systemIdentifier 
				     AND GroupName = @groupName)
			BEGIN	
				SELECT @groupidentifiernew = groupIdentifier 
				  FROM [Group] 
				 WHERE SystemIdentifier = @systemIdentifier 
				   AND GroupName = @groupName
			END
		ELSE
			BEGIN
				INSERT INTO [Group](
						SystemIdentifier, 
						GroupName) 
				VALUES (@systemIdentifier, 
						@groupName)
				
				SELECT @groupidentifiernew = scope_identity()
			END		
			
			--insert entry into dbo.PatientGroupRelation	
			INSERT INTO dbo.PatientGroupRelation(
					SystemIdentifier, 
					GroupIdentifier, 
					PatientNumberInternal)
			VALUES (@systemIdentifier,  
					@groupidentifiernew, 
					@patientnumberinternal)
			
		END															
	--select @patientInternalId PatientInternalId,  @groupId GroupIdentifier
	COMMIT TRAN AddPatient
	END TRY
	
	BEGIN CATCH	
		ROLLBACK TRAN AddPatient
	END CATCH
END


GO

/****** Object:  StoredProcedure [dbo].[DeleteMeasurementDetails]    Script Date: 01/31/2011 18:59:24 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE procedure [dbo].[DeleteMeasurementDetails]
(
	@systemIdentifier int,
	@groupIdentifier int,
	@patientNumberInternal int,
	@studyDateTimeArrStr varchar(MAX)
)
AS BEGIN
	
	DECLARE @position INT -- holds the location of the separator
	DECLARE @tempstudyDateTime varchar(MAX)

	BEGIN TRY
		BEGIN TRAN DeletePatientMeasurement
		
		WHILE PATINDEX('%,%' , @studyDateTimeArrStr) <> 0 
		BEGIN

			-- patindex matches the a pattern against a string
			SET @position =  PATINDEX('%,%' , @studyDateTimeArrStr)

			-- The following statement extracts the value from the string value
			SET @tempstudyDateTime = LEFT(@studyDateTimeArrStr, @position - 1)
			
			--delete from pwv measurement		
			DELETE from dbo.PWVMeasurement 
			 WHERE PatientNumberInternal = @patientNumberInternal 
			   AND SystemIdentifier = @systemIdentifier 
			   AND GroupIdentifier = @groupIdentifier 
			   AND StudyDateTime =  @tempstudyDateTime 

				SET @studyDateTimeArrStr = STUFF(@studyDateTimeArrStr, 1, @position, '')
	   
		  END
			
		COMMIT TRAN DeletePatientMeasurement
	END TRY
	BEGIN CATCH		
		ROLLBACK TRAN DeletePatientMeasurement
	END CATCH
END
GO

/****** Object:  StoredProcedure [dbo].[GetPWVTrendData]    Script Date: 02/17/2011 13:06:02 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO


CREATE procedure [dbo].[GetPWVTrendData]
(
	@systemIdentifier int,
	@groupIdentifier int,
	@PatientNumberInternal int,
	@studyDateTimeArrStr nvarchar(MAX),
	@heartRateArrStr nvarchar(MAX) output,
	@pulseWaveVelocityArrStr nvarchar(MAX) output,
	@StandardDeviationArrStr nvarchar(MAX) output,
	@IsStdDevValidArrStr nvarchar(MAX) output

)
AS
BEGIN

DECLARE @position INT -- holds the location of the separator
DECLARE @tempstudyDateTime VarChar(max)
DECLARE @heartRate nVarChar(max)
DECLARE @PulseWave nVarChar(max)
DECLARE @stdDev nVarChar(max)
DECLARE @isStdDev nVarChar(max)

SET @heartRateArrStr = ''
SET @pulseWaveVelocityArrStr = ''
SET @StandardDeviationArrStr = ''
SET @IsStdDevValidArrStr = ''

	WHILE PATINDEX('%,%' , @studyDateTimeArrStr) <> 0 
	BEGIN
		
		SET @heartRate = ''
		SET @PulseWave = ''
		SET @stdDev = ''
		SET @isStdDev = ''
		
		-- patindex matches the a pattern against a string
		SET @position =  PATINDEX('%,%' , @studyDateTimeArrStr)

		-- The following statement extracts the value from the string value
		SET @tempstudyDateTime = LEFT(@studyDateTimeArrStr, @position - 1)
		
		SELECT @heartRate = round([MeanHeartRate],0),
			   @PulseWave = round([MeanPulseWaveVelocity],1),
			   @stdDev = round([StandardDeviation],1),
			   @isStdDev = [IsStandardDeviationValid]

	      FROM dbo.PWVMeasurement  
		 WHERE PatientNumberInternal  =   @PatientNumberInternal  
		   AND GroupIdentifier =  + @groupIdentifier  
		   AND SystemIdentifier =  + @systemIdentifier 
		   AND studydatetime =  @tempstudyDateTime 
	
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
	END	
END 

GO


ALTER TABLE [dbo].[PatientGroupRelation]  WITH CHECK ADD  CONSTRAINT [FK_PatientGroupRelation_Group] FOREIGN KEY([SystemIdentifier], [GroupIdentifier])
REFERENCES [dbo].[Group] ([SystemIdentifier], [GroupIdentifier])
GO

ALTER TABLE [dbo].[PatientGroupRelation] CHECK CONSTRAINT [FK_PatientGroupRelation_Group]
GO

ALTER TABLE [dbo].[PatientGroupRelation]  WITH CHECK ADD  CONSTRAINT [FK_PatientGroupRelation_Patient] FOREIGN KEY([SystemIdentifier], [PatientNumberInternal])
REFERENCES [dbo].[Patient] ([SystemIdentifier], [PatientNumberInternal])
GO

ALTER TABLE [dbo].[PatientGroupRelation] CHECK CONSTRAINT [FK_PatientGroupRelation_Patient]
GO

ALTER TABLE [dbo].[PWVMeasurement]  WITH CHECK ADD  CONSTRAINT [FK_PWVMeasurement_Group] FOREIGN KEY([SystemIdentifier], [GroupIdentifier])
REFERENCES [dbo].[Group] ([SystemIdentifier], [GroupIdentifier])
GO

ALTER TABLE [dbo].[PWVMeasurement] CHECK CONSTRAINT [FK_PWVMeasurement_Group]
GO

ALTER TABLE [dbo].[PWVMeasurement]  WITH CHECK ADD  CONSTRAINT [FK_PWVMeasurement_Patient] FOREIGN KEY([SystemIdentifier], [PatientNumberInternal])
REFERENCES [dbo].[Patient] ([SystemIdentifier], [PatientNumberInternal])
ON DELETE CASCADE
GO

ALTER TABLE [dbo].[PWVMeasurement] CHECK CONSTRAINT [FK_PWVMeasurement_Patient]
GO