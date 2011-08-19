USE [AtCor]
GO

/****** Object:  StoredProcedure [dbo].[DeletePatientDetails]    Script Date: 08/02/2011 14:40:48 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO





ALTER PROCEDURE [dbo].[DeletePatientDetails]
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

