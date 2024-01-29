USE [RanUser]
GO
/****** Object:  StoredProcedure [dbo].[UserLogoutSimple2]    Script Date: 05/07/2017 14:37:39 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

ALTER PROCEDURE [dbo].[UserLogoutSimple2]
	@nUserNum int
AS
	SET NOCOUNT ON
	
	UPDATE UserInfo
	SET UserLoginState=0 
	WHERE UserNum=@nUserNum

	---PCID
	DELETE FROM UserKey 
	WHERE PCIDUserNum=@nUserNum
	
	SET NOCOUNT OFF
