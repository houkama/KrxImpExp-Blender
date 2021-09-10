///////////////////////////////////////////////////////////////////////////////
// Name:        3dsImporter.meta
// Purpose:     Main source file for "3ds file importer" program
//              This file is intended to be compiled.
// Author:      Vitaly Baranov
// Created:     January 14, 2009
// Modified by:  
// Licence:     GNU General Public License
///////////////////////////////////////////////////////////////////////////////

#ifndef _3DS_IMPORTER_META
#define _3DS_IMPORTER_META

#include "Meta.h"
#include "File.meta"
#include "ObjectStats.meta"
#include "SceneAnalyzer.meta"
#include "3dsFileLoader.meta"
#include "ObjArrayUtils.meta"
#include "3dsImporterDlgInput.meta"
#include "3dsImporterDlgOutput.meta"
#include "MeshInfoDlgInput.meta"
#include "ImpExpPathes.meta"
#include "RunUIExe.meta"

// 3DS file importer main function
IMPORT_FUNC(Krx3dsImp, T("3DS"), T("Kerrax 3D Studio Mesh"), T("Kerrax"), 2008, 1.10, 0x609516fe, 0x63690b24, 1024227)

	// analyze the scene
	LOCAL_VAR(TSceneAnalyzer, sceneAnalyzer, CALLF0(AnalyzeScene))

	// dialog input data
	LOCAL_VAR(T3DSImporterDlgInput, dlgInput, CALLF0(New3DSImporterDlgInput))
	CALLP1(dlgInput.SetImportFileName, IMPORT_FILE_NAME)
	CALLP1(dlgInput.SetImportFileSize, IMPORT_FILE_SIZE)
	CALLP1(dlgInput.SetSystemUnitsPerFileUnit, DEFAULT_SYSTEM_UNITS_PER_FILE_UNIT)
	CALLP1(dlgInput.SetCurrentSceneMode, CURSCN_REPLACE_SCENE)

	CALLP1(dlgInput.SetSlots, CALLF0(sceneAnalyzer.GetSceneSlots))
	LOCAL_VAR(TARRAY(TSTRING), selectedSlots, CALLF0(sceneAnalyzer.GetSelectedSlots))
	IF(SIZE(selectedSlots) != 0)
		CALLP1(dlgInput.SetSelectedSlot, GET_ELEM(selectedSlots, 0))
		CALLP1(dlgInput.SetCurrentSceneMode, CURSCN_REPLACE_SLOT)
	END_IF

	CALLP1(dlgInput.SetBones, CALLF0(sceneAnalyzer.GetSceneBones))
	LOCAL_VAR(TARRAY(TSTRING), selectedBones, CALLF0(sceneAnalyzer.GetSelectedBones))
	IF(SIZE(selectedBones) != 0)
		CALLP1(dlgInput.SetSelectedBone, GET_ELEM(selectedBones, 0))
		CALLP1(dlgInput.SetCurrentSceneMode, CURSCN_REPLACE_BONE)
	END_IF

	// show dialog and analyze the dialog's result
	LOCAL_VAR(T3DSImporterDlgOutput, dlgOutput, CALLF1(New3DSImporterDlgOutput, dlgInput))
	LOCAL_VAR(TFile, inputFile, CALLF0(NewFile))
	LOCAL_VAR(TFile, outputFile, CALLF0(NewFile))
	IF(NOT(QUIET))
		TRY
			SHOW_PROGRESS_BAR(T("Showing dialog"), 0)
			CALLP2(inputFile.Open, DLG_INPUT_FILE_PATH, T("wb"))
			CALLP1(inputFile.WriteString, T("3DSImporterDlgInput"))
			CALLP1(dlgInput.Write, inputFile)
			CALLP0(inputFile.Close)
			CALLP0(RunUIExe)
			CALLP2(outputFile.Open, DLG_OUTPUT_FILE_PATH, T("rb"))
			LOCAL_VAR(TSTRING, structName, CALLF0(outputFile.ReadString))
			CALLP1(dlgOutput.Read, outputFile)
			CALLP0(outputFile.Close)
			
			IF(NOT(CALLF0(dlgOutput.GetContinueImport)))
				HIDE_PROGRESS_BAR
				RETURN_VAL(IMPEXP_CANCEL)
			END_IF
		END_TRY
		CATCH
			CALLP0(inputFile.Close)
			CALLP0(outputFile.Close)
			SHOW_ERROR_BOX(T("Kerrax 3DS Importer"), CURRENT_EXCEPTION)
			HIDE_PROGRESS_BAR
			RETURN_VAL(IMPEXP_CANCEL)
		END_CATCH
	END_IF
	
	// Import itself
	LOCAL_VAR(T3DSFileLoader, loader, CALLF0(New3DSFileLoader))
	TRY
		// delete old scene objects if user wish to do it
		IF(CALLF0(dlgOutput.GetCurrentSceneMode) == CURSCN_REPLACE_SCENE)
			RESET_SCENE
		END_IF

		// load .3ds file
		LOCAL_VAR(REF(TSpaceTransform), spaceTransform, CALLF0(dlgOutput.GetSpaceTransform))
		CALLP2(loader.Read3DSFile, IMPORT_FILE_NAME, spaceTransform)
		
		// weld vertices if needed
		IF(CALLF0(dlgOutput.GetWeldVertices))
			CALLP1(loader.WeldVertices, CALLF0(dlgOutput.GetThreshold))
		END_IF
		
		// attach mesh to slot/bone if user wish to do it
		IF(CALLF0(dlgOutput.GetCurrentSceneMode) == CURSCN_REPLACE_SLOT)
			CALLP1(loader.ReplaceObjectWithLoaded, CALLF0(dlgOutput.GetSelectedSlot))
		ELSE_IF(CALLF0(dlgOutput.GetCurrentSceneMode) == CURSCN_REPLACE_BONE)
			CALLP1(loader.ReplaceObjectWithLoaded, CALLF0(dlgOutput.GetSelectedBone))
		END_IF
	END_TRY
	CATCH
		SHOW_ERROR_BOX(T("Kerrax 3DS Importer"), CURRENT_EXCEPTION)
		HIDE_PROGRESS_BAR
		RETURN_VAL(IMPEXP_FAIL)
	END_CATCH

	// Show dialog with information about import
	IF(NOT(QUIET))
		SHOW_PROGRESS_BAR(T("Showing dialog"), 98)
		LOCAL_VAR(TMeshInfoDlgInput, dlgInfo, CALLF0(NewMeshInfoDlgInput))
		CALLP1(dlgInfo.SetFileName, IMPORT_FILE_NAME)
		CALLP1(dlgInfo.SetFileSize, IMPORT_FILE_SIZE)
		CALLP1(dlgInfo.SetExportMode, FALSE)
		CALLP1(dlgInfo.SetObjectStats, CALLF0(loader.GetObjectStats))
		TRY
			CALLP2(inputFile.Open, DLG_INPUT_FILE_PATH, T("wb"))
			CALLP1(inputFile.WriteString, T("MeshInfoDlgInput"))
			CALLP1(dlgInfo.Write, inputFile)
			CALLP0(inputFile.Close)
			CALLP0(RunUIExe)
		END_TRY
		CATCH
			CALLP0(inputFile.Close)
			SHOW_ERROR_BOX(T("Kerrax 3DS Importer"), CURRENT_EXCEPTION)
		END_CATCH
	END_IF

	HIDE_PROGRESS_BAR
	RETURN_VAL(IMPEXP_SUCCESS)
END_IMPORT_FUNC

#endif // _3DS_IMPORTER_META
