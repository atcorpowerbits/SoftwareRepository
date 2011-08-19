
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

/****** Object:  Table [dbo].[PWAMeasurement]    Script Date: 06/24/2011 14:36:08 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

SET ANSI_PADDING ON
GO

CREATE TABLE [dbo].[PWAMeasurement](
      [SystemIdentifier] [nvarchar](5) NOT NULL,
      [GroupIdentifier] [int] NOT NULL,
      [PatientNumberInternal] [int] NOT NULL,
      [StudyDateTime] [datetime] NOT NULL,
      [PWA_Id] [int] IDENTITY(1,1) NOT NULL,
      [AuditChange] [datetime] NULL,
      [BloodPressureRange] [nvarchar](25) NULL,
      [BloodPressureEntryOption] [smallint] NULL,
      [Age] [smallint] NULL,
      [Notes] [nvarchar](max) NULL,
      [SP] [smallint] NULL,
      [DP] [smallint] NULL,
      [MP] [smallint] NULL,
      [Operator] [nvarchar](25) NULL,
      [WeightInKilograms] [smallint] NULL,
      [WeightInPounds] [smallint] NULL,
      [HeightInCentimetres] [smallint] NULL,
      [HeightInInches] [smallint] NULL,
      [BodyMassIndex] [float] NULL,
      [MemSpare1] [nvarchar](50) NULL,
      [MemSpare2] [nvarchar](50) NULL,
      [Simulation] [bit] NULL,
      [IntSpare2] [int] NULL,
      [FloatSpare1] [float] NULL,
      [DatarRev] [int] NULL,
      [SubType] [nvarchar](50) NULL,
      [CaptureTime] [smallint] NULL,
      [SampleRate] [int] NULL,
      [SignalUpSampleRate] [int] NULL,
      [ExppulseUpSampleRate] [int] NULL,
      [Flow] [int] NULL,
      [Medication] [nvarchar](max) NULL,
      [Message] [nvarchar](max) NULL,
      [Units] [nvarchar](max) NULL,
      [CalSP] [int] NULL,
      [CalDP] [int] NULL,
      [CalMP] [int] NULL,
      [HR] [int] NULL,
      [ED] [int] NULL,
      [CalcED] [int] NULL,
      [QualityED] [int] NULL,
      [EDMin] [int] NULL,
      [EDMax] [int] NULL,
      [EDOther] [int] NULL,
      [CaptureInput] [smallint] NULL,
      [C_RAW_SIGNALS] [varbinary](max) NULL,
      [C_AV_PULSE] [varbinary](max) NULL,
      [C_TRIGS] [varbinary](50) NULL,
      [C_ONSETS] [varbinary](50) NULL,
      [C_Uncal_Av] [varbinary](50) NULL,
      [C_ResemblePulse] [varbinary](50) NULL,
      [C_Ole_Spare] [nvarchar](max) NULL,
      [C_Math_Params] [int] NULL,
      [C_Sp] [float] NULL,
      [C_Dp] [float] NULL,
      [C_Meanp] [float] NULL,
      [C_T1] [float] NULL,
      [C_T2] [float] NULL,
      [C_T1i] [float] NULL,
      [C_T1r] [float] NULL,
      [C_T1m] [float] NULL,
      [C_T1other] [float] NULL,
      [C_T2i] [float] NULL,
      [C_T2R] [float] NULL,
      [C_T2M] [float] NULL,
      [C_T2Other] [float] NULL,
      [C_Quality_T1] [int] NULL,
      [C_Quality_T2] [int] NULL,
      [C_P1] [float] NULL,
      [C_P2] [float] NULL,
      [C_T1ED] [float] NULL,
      [C_T2ED] [float] NULL,
      [C_Ai] [float] NULL,
      [C_Esp] [float] NULL,
      [C_Ap] [float] NULL,
      [C_Mps] [float] NULL,
      [C_Mpd] [float] NULL,
      [C_Tti] [float] NULL,
      [C_Dti] [float] NULL,
      [C_Svi] [float] NULL,
      [C_Period] [float] NULL,
      [C_Dd] [float] NULL,
      [C_EdPeriod] [float] NULL,
      [C_DdPeriod] [float] NULL,
      [C_Ph] [float] NULL,
      [C_P1_Height] [float] NULL,
      [C_Agph] [float] NULL,
      [C_Qc_Other1] [float] NULL,
      [C_Qc_Other2] [float] NULL,
      [C_Qc_Other3] [float] NULL,
      [C_Qc_Other4] [float] NULL,
      [C_IntSpare1] [int] NULL,
      [C_IntSpare2] [int] NULL,
      [C_FloatSpare1] [float] NULL,
      [C_FloatSpare2] [float] NULL,
      [C_MemSpare1] [nvarchar](max) NULL,
      [C_MemSpare2] [nvarchar](max) NULL,
      [C_Al] [float] NULL,
      [C_Ati] [float] NULL,
      [C_Flow] [varbinary](50) NULL,
      [C_Forward] [varbinary](50) NULL,
      [C_Backward] [varbinary](50) NULL,
      [C_Avi] [float] NULL,
      [C_Pptt] [float] NULL,
      [C_Avd] [float] NULL,
      [C_Pwv] [float] NULL,
      [C_Forward_Area] [float] NULL,
      [C_Backward_Area] [float] NULL,
      [C_Area_Ratio] [float] NULL,
      [C_Pulse_Ratio] [float] NULL,
 CONSTRAINT [PK_PWAMeasurement_1] PRIMARY KEY CLUSTERED 
(
      [SystemIdentifier] ASC,
      [GroupIdentifier] ASC,
      [PatientNumberInternal] ASC,
      [StudyDateTime] ASC,
      [PWA_Id] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]

GO

SET ANSI_PADDING OFF
GO

/****** Object:  Index [UK_PWAMeasurement]    Script Date: 06/24/2011 14:48:52 ******/
CREATE UNIQUE NONCLUSTERED INDEX [UK_PWAMeasurement] ON [dbo].[PWAMeasurement] 
(
	[PWA_Id] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, SORT_IN_TEMPDB = OFF, IGNORE_DUP_KEY = OFF, DROP_EXISTING = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
GO


/****** Object:  Table [dbo].[cPWAMeasurement]    Script Date: 06/24/2011 14:36:25 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

SET ANSI_PADDING ON
GO

CREATE TABLE [dbo].[cPWAMeasurement](
      [PWA_Id] [int] NOT NULL,
      [P_RAW_SIGNALS] [varbinary](max) NULL,
      [P_AV_PULSE] [varbinary](max) NULL,
      [P_TRIGS] [varbinary](max) NULL,
      [P_ONSETS] [varbinary](max) NULL,
      [P_UNCAL_AV] [varbinary](max) NULL,
      [P_ResemblePulse] [varbinary](max) NULL,
      [P_OLE_SPARE] [nvarchar](max) NULL,
      [P_MATH_PARAMS] [int] NULL,
      [P_SP] [float] NULL,
      [P_DP] [float] NULL,
      [P_MEANP] [float] NULL,
      [P_T1I] [float] NULL,
      [P_T1R] [float] NULL,
      [P_T1M] [float] NULL,
      [P_T1Other] [float] NULL,
      [P_T2I] [float] NULL,
      [P_T2R] [float] NULL,
      [P_T2M] [float] NULL,
      [P_T2Other] [float] NULL,
      [P_MAX_DPDT] [float] NULL,
      [P_MEMSPARE1] [varbinary](max) NULL,
      [P_MEMSPARE2] [varbinary](max) NULL,
      [P_INTSPARE1] [int] NULL,
      [P_INTSPARE2] [int] NULL,
      [P_FLOATSPARE1] [float] NULL,
      [P_FLOATSPARE2] [float] NULL,
      [P_NOISE_FACTOR] [int] NULL,
      [P_QC_PH] [float] NULL,
      [P_QC_PHV] [float] NULL,
      [P_QC_PLV] [float] NULL,
      [P_QC_DV] [float] NULL,
      [P_QC_OTHER1] [float] NULL,
      [P_QC_OTHER2] [float] NULL,
      [P_QC_OTHER3] [float] NULL,
      [P_QC_OTHER4] [float] NULL,
 CONSTRAINT [PK_cPWAMeasurement] PRIMARY KEY CLUSTERED 
(
      [PWA_Id] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]

GO

SET ANSI_PADDING OFF
GO

/****** Object:  Table [dbo].[tPWAMeasurement]    Script Date: 06/24/2011 14:36:54 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

SET ANSI_PADDING ON
GO

CREATE TABLE [dbo].[tPWAMeasurement](
      [PWA_Id] [int] NOT NULL,
      [P_RAW_SIGNALS] [varbinary](max) NULL,
      [P_AV_PULSE] [varbinary](max) NULL,
      [P_TRIGS] [varbinary](max) NULL,
      [P_ONSETS] [varbinary](max) NULL,
      [P_UNCAL_AV] [varbinary](max) NULL,
      [P_ResemblePulse] [varbinary](max) NULL,
      [P_OLE_SPARE] [nvarchar](max) NULL,
      [P_MATH_PARAMS] [int] NULL,
      [P_SP] [float] NULL,
      [P_DP] [float] NULL,
      [P_MEANP] [float] NULL,
      [P_T1I] [float] NULL,
      [P_T1R] [float] NULL,
      [P_T1M] [float] NULL,
      [P_T1Other] [float] NULL,
      [P_T2I] [float] NULL,
      [P_T2R] [float] NULL,
      [P_T2M] [float] NULL,
      [P_T2Other] [float] NULL,
      [P_MAX_DPDT] [float] NULL,
      [P_MEMSPARE1] [float] NULL,
      [P_MEMSPARE2] [float] NULL,
      [P_INTSPARE1] [int] NULL,
      [P_INTSPARE2] [int] NULL,
      [P_FLOATSPARE1] [float] NULL,
      [P_FLOATSPARE2] [float] NULL,
      [P_NOISE_FACTOR] [int] NULL,
      [P_QC_PH] [float] NULL,
      [P_QC_PHV] [float] NULL,
      [P_QC_PLV] [float] NULL,
      [P_QC_DV] [float] NULL,
      [P_QC_OTHER1] [float] NULL,
      [P_QC_OTHER2] [float] NULL,
      [P_QC_OTHER3] [float] NULL,
      [P_QC_OTHER4] [float] NULL,
      [P_T1] [float] NULL,
      [P_T2] [float] NULL,
      [P_AI] [float] NULL,
      [P_CalcT1] [float] NULL,
      [P_CalcT2] [float] NULL,
      [P_ESP] [float] NULL,
      [P_P1] [float] NULL,
      [P_P2] [float] NULL,
      [P_T1ED] [float] NULL,
      [P_T2ED] [float] NULL,
      [P_QUALITY_T1] [int] NULL,
      [P_QUALITY_T2] [int] NULL,
 CONSTRAINT [PK_tPWAMeasurement] PRIMARY KEY CLUSTERED 
(
      [PWA_Id] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]

GO

SET ANSI_PADDING OFF
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
	
	--get the pwa measurement unique id
			
	--delete from cpwa measurement
	DELETE FROM dbo.cPWAMeasurement WHERE PWA_Id in (SELECT PWA_Id from dbo.PWAMeasurement 
			 WHERE PatientNumberInternal = @patientNumberInternal 
			   AND SystemIdentifier = @systemIdentifier 
			   AND GroupIdentifier = @groupIdentifier)
			   
	--delete from pwa measurement		
			DELETE from dbo.PWAMeasurement 
			 WHERE PatientNumberInternal = @patientNumberInternal 
			   AND SystemIdentifier = @systemIdentifier 
			   AND GroupIdentifier = @groupIdentifier 
	
	--delete from pwv measurement
	DELETE FROM dbo.PWVMeasurement WHERE PatientNumberInternal = @patientNumberInternal and SystemIdentifier = @systemIdentifier and GroupIdentifier = @groupIdentifier
	
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
/****** Object:  StoredProcedure [dbo].[InsertCuffPWAMeasurementDetails]    Script Date: 07/20/2011 14:11:00 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO


CREATE PROCEDURE [dbo].[InsertCuffPWAMeasurementDetails]
(
	@systemIdentifier nvarchar(5) ,
	@groupIdentifier int ,
	@PatientNumberInternal int ,
	--@auditChange datetime ,
	@bloodPressureRange nvarchar(max) ,
	@bloodPressureEntryOption smallint ,
	@age smallint ,
	@notes nvarchar(max) ,
	@SP smallint ,
	@DP smallint ,
	@MP smallint ,
	@operator nvarchar(25),
	@weightInKilograms smallint ,
	@weightInPounds smallint ,
	@heightInCentimetres smallint ,
	@heightInInches smallint ,
	@bodyMassIndex float ,
	@memSpare1 nvarchar(50) ,
	@memSpare2 nvarchar(50) ,
	@simulation bit,
	@intSpare2 int ,
	@floatSpare1 float ,
	@datarRev int ,
	@subType nvarchar(50) ,
	@captureTime smallint,
	@sampleRate int ,
	@signalUpSampleRate int ,
	@expPulseUpSampleRate int ,
	@flow int ,
	@medication nvarchar(max) ,
	@message nvarchar(max) ,
	@units nvarchar(max) ,
	@calSP int ,
	@calDP int ,
	@calMP int ,
	@hR int ,
	@eD int ,
	@calcED int ,
	@QualityED int ,
	@eDMin int ,
	@eDMax int ,
	@eDOther int ,
	@captureInput smallint ,
	@c_RAW_SIGNALS varbinary(max) ,
	@c_AV_PULSE varbinary(max) ,
	@c_TRIGS varbinary(50) ,
	@c_ONSETS varbinary(50) ,
	@c_Uncal_Av varbinary(50) ,
	@c_ResemblePulse varbinary(50) ,
	@c_Ole_Spare nvarchar(max),
	@c_Math_Params int ,
	@c_Sp float ,
	@c_Dp float ,
	@c_Meanp float ,
	@c_T1 float ,
	@c_T2 float ,
	@c_T1i float ,
	@c_T1r float ,
	@c_T1m float ,
	@c_T1other float ,
	@c_T2i float ,
	@c_T2R float ,
	@c_T2M float ,
	@c_T2Other float ,
	@c_Quality_T1 int ,
	@c_Quality_T2 int ,
	@c_P1 float ,
	@c_P2 float ,
	@c_T1ED float ,
	@c_T2ED float ,
	@c_Ai float ,
	@c_Esp float ,
	@c_Ap float ,
	@c_Mps float ,
	@c_Mpd float ,
	@c_Tti float ,
	@c_Dti float ,
	@c_Svi float ,
	@c_Period float ,
	@c_Dd float ,
	@c_EdPeriod float ,
	@c_DdPeriod float ,
	@c_Ph float ,
	@c_P1_Height float ,
	@c_Agph float ,
	@c_Qc_Other1 float ,
	@c_Qc_Other2 float ,
	@c_Qc_Other3 float ,
	@c_Qc_Other4 float ,
	@c_IntSpare1 int ,
	@c_IntSpare2 int ,
	@c_FloatSpare1 float ,
	@c_FloatSpare2 float ,
	@c_MemSpare1 nvarchar(max) ,
	@c_MemSpare2 nvarchar(max) ,
	@c_Al float ,
	@c_Ati float ,
	@c_Flow varbinary(50) ,
	@c_Forward varbinary(50) ,
	@c_Backward varbinary(50) ,
	@c_Avi float ,
	@c_Pptt float ,
	@c_Avd float ,
	@c_Pwv float ,
	@c_Forward_Area float ,
	@c_Backward_Area float ,
	@c_Area_Ratio float ,
	@c_Pulse_Ratio float,
	---------------------------
	@p_Raw_Signals	varbinary(MAX),
	@p_Av_Pulses	varbinary(MAX),
	@p_Trigs	varbinary(MAX),
	@p_Onsets	varbinary(MAX),
	@p_Uncal_Av	varbinary(MAX),
	@p_ResemblePulse	varbinary(MAX),
	@p_Ole_Spare	nvarchar(MAX),
	@p_Math_Params	int,
	@p_Sp	float,
	@p_Dp	float,
	@p_Meanp	float,
	@p_T1i	float,
	@p_T1r	float,
	@p_T1m	float,
	@p_T1other	float,
	@p_T2i	float,
	@p_T2r	float,
	@p_T2m	float,
	@p_T2other	float,
	@p_Max_Dpdt	float,
	@p_Memspare1	varbinary(MAX),
	@p_Memspare2	varbinary(MAX),
	@p_Intspare1	int,
	@p_Intspare2	int,
	@p_Floatspare1	float,
	@p_Floatspare2	float,
	@p_Noise_Factor	int,
	@p_Qc_Ph	float,
	@p_Qc_Phv	float,
	@p_Qc_Plv	float,
	@p_Qc_Dv	float,
	@p_Qc_Other1	float,
	@p_Qc_Other2	float,
	@p_Qc_Other3	float,
	@p_Qc_Other4	float		
)
AS
BEGIN

	DECLARE @measurementDetailsdatetime datetime2(0)
	DECLARE @auditChange datetime2(0)
	DECLARE @Pwa_id int
	BEGIN TRY
	BEGIN TRAN AddMeasurementData
	
	SET @measurementDetailsdatetime = Getdate()
	SET @auditChange = @measurementDetailsdatetime
	
		--insert into PWVMeasurement
	
		insert into  dbo.PWAMeasurement
		(
			SystemIdentifier,
			GroupIdentifier,
			PatientNumberInternal,
			StudyDateTime,
			AuditChange,
			BloodPressureRange,
			BloodPressureEntryOption,
			Age,
			Notes,
			SP,
			DP,
			MP,
			Operator,
			WeightInKilograms,
			WeightInPounds,
			HeightInCentimetres,
			HeightInInches,
			BodyMassIndex,
			MemSpare1,
			MemSpare2,
			Simulation,
			IntSpare2,
			FloatSpare1,
			DatarRev,
			SubType,
			CaptureTime,
			SampleRate,
			SignalUpSampleRate,
			ExppulseUpSampleRate,
			Flow,
			Medication,
			Message,
			Units,
			CalSP,
			CalDP,
			CalMP,
			HR,
			ED,
			CalcED,
			QualityED,
			EDMin,
			EDMax,
			EDOther,
			CaptureInput,
			C_RAW_SIGNALS,
			C_AV_PULSE,
			C_TRIGS,
			C_ONSETS,
			C_Uncal_Av,
			C_ResemblePulse,
			C_Ole_Spare,
			C_Math_Params,
			C_Sp,
			C_Dp,
			C_Meanp,
			C_T1,
			C_T2,
			C_T1i,
			C_T1r,
			C_T1m,
			C_T1other,
			C_T2i,
			C_T2R,
			C_T2M,
			C_T2Other,
			C_Quality_T1,
			C_Quality_T2,
			C_P1,
			C_P2,
			C_T1ED,
			C_T2ED,
			C_Ai,
			C_Esp,
			C_Ap,
			C_Mps,
			C_Mpd,
			C_Tti,
			C_Dti,
			C_Svi,
			C_Period,
			C_Dd,
			C_EdPeriod,
			C_DdPeriod,
			C_Ph,
			C_P1_Height,
			C_Agph,
			C_Qc_Other1,
			C_Qc_Other2,
			C_Qc_Other3,
			C_Qc_Other4,
			C_IntSpare1,
			C_IntSpare2,
			C_FloatSpare1,
			C_FloatSpare2,
			C_MemSpare1,
			C_MemSpare2,
			C_Al,
			C_Ati,
			C_Flow,
			C_Forward,
			C_Backward,
			C_Avi,
			C_Pptt,
			C_Avd,
			C_Pwv,
			C_Forward_Area,
			C_Backward_Area,
			C_Area_Ratio,
			C_Pulse_Ratio
		)
		values 
		(
				@systemIdentifier,
				@groupIdentifier,
				@PatientNumberInternal,
				@measurementDetailsdatetime,
				@auditChange,
				@bloodPressureRange,
				@bloodPressureEntryOption,
				@age,
				@notes,
				@SP,
				@DP,
				@MP,
				@operator,
				@weightInKilograms,
				@weightInPounds,
				@heightInCentimetres,
				@heightInInches,
				@bodyMassIndex,
				@memSpare1 ,
				@memSpare2 ,
				@simulation ,
				@intSpare2,
				@floatSpare1,
				@datarRev,
				@subType ,
				@captureTime,
				@sampleRate,
				@signalUpSampleRate,
				@expPulseUpSampleRate,
				@flow,
				@medication,
				@message,
				@units,
				@calSP,
				@calDP,
				@calMP,
				@hR,
				@eD,
				@calcED,
				@QualityED,
				@eDMin,
				@eDMax,
				@eDOther,
				@captureInput,
				@c_RAW_SIGNALS  ,
				@c_AV_PULSE  ,
				@c_TRIGS ,
				@c_ONSETS ,
				@c_Uncal_Av ,
				@c_ResemblePulse ,
				@c_Ole_Spare ,
				@c_Math_Params,
				@c_Sp,
				@c_Dp,
				@c_Meanp,
				@c_T1,
				@c_T2,
				@c_T1i,
				@c_T1r,
				@c_T1m,
				@c_T1other,
				@c_T2i,
				@c_T2R,
				@c_T2M,
				@c_T2Other,
				@c_Quality_T1,
				@c_Quality_T2,
				@c_P1,
				@c_P2,
				@c_T1ED,
				@c_T2ED,
				@c_Ai,
				@c_Esp,
				@c_Ap,
				@c_Mps,
				@c_Mpd,
				@c_Tti,
				@c_Dti,
				@c_Svi,
				@c_Period,
				@c_Dd,
				@c_EdPeriod,
				@c_DdPeriod,
				@c_Ph,
				@c_P1_Height,
				@c_Agph,
				@c_Qc_Other1,
				@c_Qc_Other2,
				@c_Qc_Other3,
				@c_Qc_Other4,
				@c_IntSpare1,
				@c_IntSpare2,
				@c_FloatSpare1,
				@c_FloatSpare2,
				@c_MemSpare1,
				@c_MemSpare2,
				@c_Al,
				@c_Ati,
				@c_Flow ,
				@c_Forward ,
				@c_Backward ,
				@c_Avi,
				@c_Pptt,
				@c_Avd,
				@c_Pwv,
				@c_Forward_Area,
				@c_Backward_Area,
				@c_Area_Ratio,
				@c_Pulse_Ratio
		)
	
		--fetch identity value of record inserted	
		set @Pwa_id = scope_identity()
		
		--insert entry into dbo.cPWAMeasurement
		INSERT INTO dbo.cPWAMeasurement
		(
			PWA_Id,
			P_RAW_SIGNALS,
			P_AV_PULSE,
			P_TRIGS,
			P_ONSETS,
			P_UNCAL_AV,
			P_ResemblePulse,
			P_OLE_SPARE,
			P_MATH_PARAMS,
			P_SP,
			P_DP,
			P_MEANP,
			P_T1I,
			P_T1R,
			P_T1M,
			P_T1Other,
			P_T2I,
			P_T2R,
			P_T2M,
			P_T2Other,
			P_MAX_DPDT,
			P_MEMSPARE1,
			P_MEMSPARE2,
			P_INTSPARE1,
			P_INTSPARE2,
			P_FLOATSPARE1,
			P_FLOATSPARE2,
			P_NOISE_FACTOR,
			P_QC_PH,
			P_QC_PHV,
			P_QC_PLV,
			P_QC_DV,
			P_QC_OTHER1,
			P_QC_OTHER2,
			P_QC_OTHER3,
			P_QC_OTHER4
		)
		values
		(
			@Pwa_id,
			@p_Raw_Signals,
			@p_Av_Pulses,
			@p_Trigs,
			@p_Onsets,
			@p_Uncal_Av,
			@p_ResemblePulse,
			@p_Ole_Spare,
			@p_Math_Params,
			@p_Sp,
			@p_Dp,
			@p_Meanp,
			@p_T1i,
			@p_T1r,
			@p_T1m,
			@p_T1other,
			@p_T2i,
			@p_T2r,
			@p_T2m,
			@p_T2other,
			@p_Max_Dpdt,
			@p_Memspare1,
			@p_Memspare2,
			@p_Intspare1,
			@p_Intspare2,
			@p_Floatspare1,
			@p_Floatspare2,
			@p_Noise_Factor,
			@p_Qc_Ph,
			@p_Qc_Phv,
			@p_Qc_Plv,
			@p_Qc_Dv,
			@p_Qc_Other1,
			@p_Qc_Other2,
			@p_Qc_Other3,
			@p_Qc_Other4				
		)	

	COMMIT TRAN AddMeasurementData
	END TRY
	BEGIN CATCH
	 DECLARE @ErrorMessage NVARCHAR(4000);
	 --SELECT @ErrorMessage =	ERROR_MESSAGE();
		ROLLBACK TRAN AddMeasurementData
	END CATCH
	

END

GO

/****** Object:  StoredProcedure [dbo].[DeleteCuffPWAMeasurementDetails]    Script Date: 07/22/2011 12:32:30 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO


CREATE procedure [dbo].[DeleteCuffPWAMeasurementDetails]
(
	@systemIdentifier int,
	@groupIdentifier int,
	@patientNumberInternal int,
	@studyDateTimeArrStr varchar(MAX)
)
AS BEGIN
	
	DECLARE @position INT -- holds the location of the separator
	DECLARE @tempstudyDateTime varchar(MAX)
	DECLARE @PWAID INT

	BEGIN TRY
		BEGIN TRAN DeletePatientMeasurement
		
		WHILE PATINDEX('%,%' , @studyDateTimeArrStr) <> 0 
		BEGIN

			-- patindex matches the a pattern against a string
			SET @position =  PATINDEX('%,%' , @studyDateTimeArrStr)

			-- The following statement extracts the value from the string value
			SET @tempstudyDateTime = LEFT(@studyDateTimeArrStr, @position - 1)
			
			--get the pwa measurement unique id
			SELECT @PWAID = PWA_Id from dbo.PWAMeasurement 
			 WHERE PatientNumberInternal = @patientNumberInternal 
			   AND SystemIdentifier = @systemIdentifier 
			   AND GroupIdentifier = @groupIdentifier 
			   AND StudyDateTime =  @tempstudyDateTime
			  
			 --delete from cuff pwv measurement
			 DELETE from dbo.cPWAMeasurement
			 WHERE PWA_Id = @PWAID			 
			   
			--delete from pwv measurement		
			DELETE from dbo.PWAMeasurement 
			WHERE PWA_Id = @PWAID	
			 --WHERE PatientNumberInternal = @patientNumberInternal 
			 --  AND SystemIdentifier = @systemIdentifier 
			 --  AND GroupIdentifier = @groupIdentifier 
			 --  AND StudyDateTime =  @tempstudyDateTime
			 --  AND PWA_Id = @PWAID

				SET @studyDateTimeArrStr = STUFF(@studyDateTimeArrStr, 1, @position, '')
	   
		  END
			
		COMMIT TRAN DeletePatientMeasurement
	END TRY
	BEGIN CATCH		
		ROLLBACK TRAN DeletePatientMeasurement
	END CATCH
END

GO

/****** Object:  StoredProcedure [dbo].[UpdateCuffPWAMeasurementDetails]    Script Date: 07/22/2011 14:27:57 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO



CREATE PROCEDURE [dbo].[UpdateCuffPWAMeasurementDetails]
(
	@systemIdentifier nvarchar(5) ,
	@groupIdentifier int ,
	@PatientNumberInternal int ,
	@studyDateTime datetime,
	@Pwa_id int,
	@auditChange datetime ,
	@bloodPressureRange nvarchar(max) ,
	@bloodPressureEntryOption smallint ,
	@age smallint ,
	@notes nvarchar(max) ,
	@SP smallint ,
	@DP smallint ,
	@MP smallint ,
	@operator nvarchar(25),
	@weightInKilograms smallint ,
	@weightInPounds smallint ,
	@heightInCentimetres smallint ,
	@heightInInches smallint ,
	@bodyMassIndex float ,
	@memSpare1 nvarchar(50) ,
	@memSpare2 nvarchar(50) ,
	@simulation bit,
	@intSpare2 int ,
	@floatSpare1 float ,
	@datarRev int ,
	@subType nvarchar(50) ,
	@captureTime smallint,
	@sampleRate int ,
	@signalUpSampleRate int ,
	@expPulseUpSampleRate int ,
	@flow int ,
	@medication nvarchar(max) ,
	@message nvarchar(max) ,
	@units nvarchar(max) ,
	@calSP int ,
	@calDP int ,
	@calMP int ,
	@hR int ,
	@eD int ,
	@calcED int ,
	@QualityED int ,
	@eDMin int ,
	@eDMax int ,
	@eDOther int ,
	@captureInput smallint ,
	@c_RAW_SIGNALS varbinary(max) ,
	@c_AV_PULSE varbinary(max) ,
	@c_TRIGS varbinary(50) ,
	@c_ONSETS varbinary(50) ,
	@c_Uncal_Av varbinary(50) ,
	@c_ResemblePulse varbinary(50) ,
	@c_Ole_Spare nvarchar(max),
	@c_Math_Params int ,
	@c_Sp float ,
	@c_Dp float ,
	@c_Meanp float ,
	@c_T1 float ,
	@c_T2 float ,
	@c_T1i float ,
	@c_T1r float ,
	@c_T1m float ,
	@c_T1other float ,
	@c_T2i float ,
	@c_T2R float ,
	@c_T2M float ,
	@c_T2Other float ,
	@c_Quality_T1 int ,
	@c_Quality_T2 int ,
	@c_P1 float ,
	@c_P2 float ,
	@c_T1ED float ,
	@c_T2ED float ,
	@c_Ai float ,
	@c_Esp float ,
	@c_Ap float ,
	@c_Mps float ,
	@c_Mpd float ,
	@c_Tti float ,
	@c_Dti float ,
	@c_Svi float ,
	@c_Period float ,
	@c_Dd float ,
	@c_EdPeriod float ,
	@c_DdPeriod float ,
	@c_Ph float ,
	@c_P1_Height float ,
	@c_Agph float ,
	@c_Qc_Other1 float ,
	@c_Qc_Other2 float ,
	@c_Qc_Other3 float ,
	@c_Qc_Other4 float ,
	@c_IntSpare1 int ,
	@c_IntSpare2 int ,
	@c_FloatSpare1 float ,
	@c_FloatSpare2 float ,
	@c_MemSpare1 nvarchar(max) ,
	@c_MemSpare2 nvarchar(max) ,
	@c_Al float ,
	@c_Ati float ,
	@c_Flow varbinary(50) ,
	@c_Forward varbinary(50) ,
	@c_Backward varbinary(50) ,
	@c_Avi float ,
	@c_Pptt float ,
	@c_Avd float ,
	@c_Pwv float ,
	@c_Forward_Area float ,
	@c_Backward_Area float ,
	@c_Area_Ratio float ,
	@c_Pulse_Ratio float,
	---------------------------
	@p_Raw_Signals	varbinary(MAX),
	@p_Av_Pulses	varbinary(MAX),
	@p_Trigs	varbinary(MAX),
	@p_Onsets	varbinary(MAX),
	@p_Uncal_Av	varbinary(MAX),
	@p_ResemblePulse	varbinary(MAX),
	@p_Ole_Spare	nvarchar(MAX),
	@p_Math_Params	int,
	@p_Sp	float,
	@p_Dp	float,
	@p_Meanp	float,
	@p_T1i	float,
	@p_T1r	float,
	@p_T1m	float,
	@p_T1other	float,
	@p_T2i	float,
	@p_T2r	float,
	@p_T2m	float,
	@p_T2other	float,
	@p_Max_Dpdt	float,
	@p_Memspare1	varbinary(MAX),
	@p_Memspare2	varbinary(MAX),
	@p_Intspare1	int,
	@p_Intspare2	int,
	@p_Floatspare1	float,
	@p_Floatspare2	float,
	@p_Noise_Factor	int,
	@p_Qc_Ph	float,
	@p_Qc_Phv	float,
	@p_Qc_Plv	float,
	@p_Qc_Dv	float,
	@p_Qc_Other1	float,
	@p_Qc_Other2	float,
	@p_Qc_Other3	float,
	@p_Qc_Other4	float		
)
AS
BEGIN

	DECLARE @measurementDetailsdatetime datetime2(0)
	DECLARE @measurementauditChange datetime2(0)
	--DECLARE @Pwa_id int
	BEGIN TRY
	BEGIN TRAN UpdateMeasurementData
	
	SET @measurementDetailsdatetime = Getdate()
	SET @measurementauditChange = @measurementDetailsdatetime
	
	--Update PWA Measurement record
		UPDATE dbo.PWAMeasurement SET
		SystemIdentifier		=	@systemIdentifier,
		GroupIdentifier			=	@groupIdentifier,
		PatientNumberInternal	=	@PatientNumberInternal,
		StudyDateTime			=	@studyDateTime,
		AuditChange				=	@measurementauditChange,
		BloodPressureRange		=	@bloodPressureRange,
		BloodPressureEntryOption	=	@bloodPressureEntryOption,
		Age		=	@age,
		Notes	=	@notes,
		SP		=	@SP,
		DP		=	@DP,
		MP		=	@MP,
		Operator				=	@operator,
		WeightInKilograms		=	@weightInKilograms,
		WeightInPounds			=	@weightInPounds,
		HeightInCentimetres		=	@heightInCentimetres,
		HeightInInches			=	@heightInInches,
		BodyMassIndex			=	@bodyMassIndex,
		MemSpare1	=	@memSpare1 ,
		MemSpare2	=	@memSpare2 ,
		Simulation	=	@simulation ,
		IntSpare2	=	@intSpare2,
		FloatSpare1	=	@floatSpare1,
		DatarRev	=	@datarRev,
		SubType		=	@subType ,
		CaptureTime =   @captureTime,
		SampleRate	=	@sampleRate,
		SignalUpSampleRate		=	@signalUpSampleRate,
		ExppulseUpSampleRate	=	@expPulseUpSampleRate,
		Flow		=	@flow,
		Medication	=	@medication,
		Message		=	@message,
		Units		=	@units,
		CalSP		=	@calSP,
		CalDP		=	@calDP,
		CalMP		=	@calMP,
		HR			=	@hR,
		ED			=	@eD,
		CalcED		=	@calcED,
		QualityED	=	@QualityED,
		EDMin		=	@eDMin,
		EDMax		=	@eDMax,
		EDOther		=	@eDOther,
		CaptureInput	=	@captureInput,
		C_RAW_SIGNALS	=	@c_RAW_SIGNALS  ,
		C_AV_PULSE		=	@c_AV_PULSE  ,
		C_TRIGS			=	@c_TRIGS ,
		C_ONSETS		=	@c_ONSETS ,
		C_Uncal_Av		=	@c_Uncal_Av ,
		C_ResemblePulse	=	@c_ResemblePulse ,
		C_Ole_Spare		=	@c_Ole_Spare ,
		C_Math_Params	=	@c_Math_Params,
		C_Sp	=	@c_Sp,
		C_Dp	=	@c_Dp,
		C_Meanp	=	@c_Meanp,
		C_T1	=	@c_T1,
		C_T2	=	@c_T2,
		C_T1i	=	@c_T1i,
		C_T1r	=	@c_T1r,
		C_T1m	=	@c_T1m,
		C_T1other	=	@c_T1other,
		C_T2i	=	@c_T2i,
		C_T2R	=	@c_T2R,
		C_T2M	=	@c_T2M,
		C_T2Other		=	@c_T2Other,
		C_Quality_T1	=	@c_Quality_T1,
		C_Quality_T2	=	@c_Quality_T2,
		C_P1	=	@c_P1,
		C_P2	=	@c_P2,
		C_T1ED	=	@c_T1ED,
		C_T2ED	=	@c_T2ED,
		C_Ai	=	@c_Ai,
		C_Esp	=	@c_Esp,
		C_Ap	=	@c_Ap,
		C_Mps	=	@c_Mps,
		C_Mpd	=	@c_Mpd,
		C_Tti	=	@c_Tti,
		C_Dti	=	@c_Dti,
		C_Svi	=	@c_Svi,
		C_Period	=	@c_Period,
		C_Dd		=	@c_Dd,
		C_EdPeriod	=	@c_EdPeriod,
		C_DdPeriod	=	@c_DdPeriod,
		C_Ph		=	@c_Ph,
		C_P1_Height	=	@c_P1_Height,
		C_Agph		=	@c_Agph,
		C_Qc_Other1	=	@c_Qc_Other1,
		C_Qc_Other2	=	@c_Qc_Other2,
		C_Qc_Other3	=	@c_Qc_Other3,
		C_Qc_Other4	=	@c_Qc_Other4,
		C_IntSpare1	=	@c_IntSpare1,
		C_IntSpare2	=	@c_IntSpare2,
		C_FloatSpare1	=	@c_FloatSpare1,
		C_FloatSpare2	=	@c_FloatSpare2,
		C_MemSpare1		=	@c_MemSpare1,
		C_MemSpare2		=	@c_MemSpare2,
		C_Al	=	@c_Al,
		C_Ati	=	@c_Ati,
		C_Flow	=	@c_Flow ,
		C_Forward	=	@c_Forward ,
		C_Backward	=	@c_Backward ,
		C_Avi	=	@c_Avi,
		C_Pptt	=	@c_Pptt,
		C_Avd	=	@c_Avd,
		C_Pwv	=	@c_Pwv,
		C_Forward_Area	=	@c_Forward_Area,
		C_Backward_Area	=	@c_Backward_Area,
		C_Area_Ratio	=	@c_Area_Ratio,
		C_Pulse_Ratio	=	@c_Pulse_Ratio
		WHERE  PWA_Id= @Pwa_id
	
		--fetch identity value of record inserted	
		--set @Pwa_id = scope_identity()
		
		--Update entry into dbo.cPWAMeasurement
		UPDATE dbo.cPWAMeasurement SET
		P_RAW_SIGNALS	=	@p_Raw_Signals,
		P_AV_PULSE		=	@p_Av_Pulses,
		P_TRIGS			=	@p_Trigs,
		P_ONSETS		=	@p_Onsets,
		P_UNCAL_AV		=	@p_Uncal_Av,
		P_ResemblePulse	=	@p_ResemblePulse,
		P_OLE_SPARE		=	@p_Ole_Spare,
		P_MATH_PARAMS	=	@p_Math_Params,
		P_SP	=	@p_Sp,
		P_DP	=	@p_Dp,
		P_MEANP	=	@p_Meanp,
		P_T1I	=	@p_T1i,
		P_T1R	=	@p_T1r,
		P_T1M	=	@p_T1m,
		P_T1Other	=	@p_T1other,
		P_T2I	=	@p_T2i,
		P_T2R	=	@p_T2r,
		P_T2M	=	@p_T2m,
		P_T2Other	=	@p_T2other,
		P_MAX_DPDT	=	@p_Max_Dpdt,
		P_MEMSPARE1	=	@p_Memspare1,
		P_MEMSPARE2	=	@p_Memspare2,
		P_INTSPARE1	=	@p_Intspare1,
		P_INTSPARE2	=	@p_Intspare2,
		P_FLOATSPARE1	=	@p_Floatspare1,
		P_FLOATSPARE2	=	@p_Floatspare2,
		P_NOISE_FACTOR	=	@p_Noise_Factor,
		P_QC_PH		=	@p_Qc_Ph,
		P_QC_PHV	=	@p_Qc_Phv,
		P_QC_PLV	=	@p_Qc_Plv,
		P_QC_DV		=	@p_Qc_Dv,
		P_QC_OTHER1	=	@p_Qc_Other1,
		P_QC_OTHER2	=	@p_Qc_Other2,
		P_QC_OTHER3	=	@p_Qc_Other3,
		P_QC_OTHER4	=	@p_Qc_Other4
		WHERE  PWA_Id= @Pwa_id

	COMMIT TRAN UpdateMeasurementData
	END TRY
	BEGIN CATCH
	 DECLARE @ErrorMessage NVARCHAR(4000);
	 --SELECT @ErrorMessage =	ERROR_MESSAGE();
		ROLLBACK TRAN UpdateMeasurementData
	END CATCH
	

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

ALTER TABLE [dbo].[PWVMeasurement]  WITH CHECK ADD  CONSTRAINT [FK_PWVMeasurement_PatientGroupRelation] FOREIGN KEY([SystemIdentifier], [GroupIdentifier], [PatientNumberInternal])
REFERENCES [dbo].[PatientGroupRelation] ([SystemIdentifier], [GroupIdentifier], [PatientNumberInternal])
GO

ALTER TABLE [dbo].[PWVMeasurement] CHECK CONSTRAINT [FK_PWVMeasurement_PatientGroupRelation]
GO

ALTER TABLE [dbo].[PWAMeasurement]  WITH CHECK ADD  CONSTRAINT [FK_PWAMeasurement_Group] FOREIGN KEY([SystemIdentifier], [GroupIdentifier], [PatientNumberInternal])
REFERENCES [dbo].[PatientGroupRelation] ([SystemIdentifier], [GroupIdentifier], [PatientNumberInternal])
GO

ALTER TABLE [dbo].[PWAMeasurement] CHECK CONSTRAINT [FK_PWAMeasurement_Group]
GO

ALTER TABLE [dbo].[cPWAMeasurement]  WITH CHECK ADD  CONSTRAINT [FK_cPWAMeasurement_PWAMeasurement] FOREIGN KEY([PWA_Id])
REFERENCES [dbo].[PWAMeasurement] ([PWA_Id])
GO

ALTER TABLE [dbo].[cPWAMeasurement] CHECK CONSTRAINT [FK_cPWAMeasurement_PWAMeasurement]
GO

ALTER TABLE [dbo].[tPWAMeasurement]  WITH CHECK ADD  CONSTRAINT [FK_tPWAMeasurement_PWAMeasurement] FOREIGN KEY([PWA_Id])
REFERENCES [dbo].[PWAMeasurement] ([PWA_Id])
GO

ALTER TABLE [dbo].[tPWAMeasurement] CHECK CONSTRAINT [FK_tPWAMeasurement_PWAMeasurement]
GO

