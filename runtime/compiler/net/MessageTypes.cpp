/*******************************************************************************
 * Copyright IBM Corp. and others 2021
 *
 * This program and the accompanying materials are made available under
 * the terms of the Eclipse Public License 2.0 which accompanies this
 * distribution and is available at https://www.eclipse.org/legal/epl-2.0/
 * or the Apache License, Version 2.0 which accompanies this distribution and
 * is available at https://www.apache.org/licenses/LICENSE-2.0.
 *
 * This Source Code may also be made available under the following
 * Secondary Licenses when the conditions for such availability set
 * forth in the Eclipse Public License, v. 2.0 are satisfied: GNU
 * General Public License, version 2 with the GNU Classpath
 * Exception [1] and GNU General Public License, version 2 with the
 * OpenJDK Assembly Exception [2].
 *
 * [1] https://www.gnu.org/software/classpath/license.html
 * [2] https://openjdk.org/legal/assembly-exception.html
 *
 * SPDX-License-Identifier: EPL-2.0 OR Apache-2.0 OR GPL-2.0-only WITH Classpath-exception-2.0 OR GPL-2.0-only WITH OpenJDK-assembly-exception-1.0
 *******************************************************************************/

#include "net/MessageTypes.hpp"

namespace JITServer
   {
const char *messageNames[] =
   {
   "compilationCode",
   "compilationFailure",
   "AOTCache_storedAOTMethod",
   "AOTCache_serializedAOTMethod",
   "AOTCache_failure",
   "mirrorResolvedJ9Method",
   "get_params_to_construct_TR_j9method",
   "getUnloadedClassRangesAndCHTable",
   "compilationRequest",
   "compilationInterrupted",
   "clientSessionTerminate",
   "connectionTerminate",
   "compilationThreadCrashed",
   "jitDumpPrintIL",
   "ResolvedMethod_setRecognizedMethodInfo",
   "ResolvedMethod_startAddressForInterpreterOfJittedMethod",
   "ResolvedMethod_staticAttributes",
   "ResolvedMethod_getClassFromConstantPool",
   "ResolvedMethod_getDeclaringClassFromFieldOrStatic",
   "ResolvedMethod_classOfStatic",
   "ResolvedMethod_startAddressForJNIMethod",
   "ResolvedMethod_fieldAttributes",
   "ResolvedMethod_getResolvedStaticMethodAndMirror",
   "ResolvedMethod_getResolvedSpecialMethodAndMirror",
   "ResolvedMethod_startAddressForJittedMethod",
   "ResolvedMethod_localName",
   "ResolvedMethod_getResolvedPossiblyPrivateVirtualMethodAndMirror",
   "ResolvedMethod_getResolvedInterfaceMethod_2",
   "ResolvedMethod_getResolvedInterfaceMethodAndMirror_3",
   "ResolvedMethod_getResolvedInterfaceMethodOffset",
   "ResolvedMethod_getUnresolvedStaticMethodInCP",
   "ResolvedMethod_isSubjectToPhaseChange",
   "ResolvedMethod_getUnresolvedSpecialMethodInCP",
   "ResolvedMethod_getUnresolvedFieldInCP",
   "ResolvedMethod_getRemoteROMClassAndMethods",
   "ResolvedMethod_getResolvedHandleMethod",
   "ResolvedMethod_isUnresolvedMethodTypeTableEntry",
   "ResolvedMethod_methodTypeTableEntryAddress",
   "ResolvedMethod_isUnresolvedCallSiteTableEntry",
   "ResolvedMethod_callSiteTableEntryAddress",
   "ResolvedMethod_getResolvedDynamicMethod",
   "ResolvedMethod_shouldFailSetRecognizedMethodInfoBecauseOfHCR",
   "ResolvedMethod_isSameMethod",
   "ResolvedMethod_isInlineable",
   "ResolvedMethod_setWarmCallGraphTooBig",
   "ResolvedMethod_setVirtualMethodIsOverridden",
   "ResolvedMethod_methodIsNotzAAPEligible",
   "ResolvedMethod_setClassForNewInstance",
   "ResolvedMethod_getResolvedImproperInterfaceMethodAndMirror",
   "ResolvedMethod_isUnresolvedString",
   "ResolvedMethod_stringConstant",
   "ResolvedMethod_getResolvedVirtualMethod",
   "ResolvedMethod_getMultipleResolvedMethods",
#if defined(J9VM_OPT_METHOD_HANDLE)
   "ResolvedMethod_varHandleMethodTypeTableEntryAddress",
   "ResolvedMethod_isUnresolvedVarHandleMethodTypeTableEntry",
#endif /* defined(J9VM_OPT_METHOD_HANDLE) */
   "ResolvedMethod_getConstantDynamicTypeFromCP",
   "ResolvedMethod_isUnresolvedConstantDynamic",
   "ResolvedMethod_dynamicConstant",
   "ResolvedMethod_definingClassFromCPFieldRef",
   "ResolvedMethod_getResolvedImplementorMethods",
   "ResolvedMethod_isFieldNullRestricted",
   "ResolvedMethod_isFieldFlattened",
   "ResolvedRelocatableMethod_createResolvedRelocatableJ9Method",
   "ResolvedRelocatableMethod_fieldAttributes",
   "ResolvedRelocatableMethod_staticAttributes",
   "ResolvedRelocatableMethod_getFieldType",
   "VM_isClassLibraryMethod",
   "VM_isClassArray",
   "VM_transformJlrMethodInvoke",
   "VM_getSystemClassFromClassName",
   "VM_isMethodTracingEnabled",
   "VM_getClassClassPointer",
   "VM_setJ2IThunk",
   "VM_getClassOfMethod",
   "VM_getClassFromSignature",
   "VM_jitFieldsOrStaticsAreSame",
   "VM_classHasBeenExtended",
   "VM_compiledAsDLTBefore",
   "VM_isThunkArchetype",
   "VM_printTruncatedSignature",
   "VM_getStaticHookAddress",
   "VM_isClassInitialized",
   "VM_getOSRFrameSizeInBytes",
   "VM_getInitialLockword",
   "VM_JavaStringObject",
   "VM_getMethods",
   "VM_getObjectClass",
   "VM_getObjectClassAt",
   "VM_getObjectClassFromKnownObjectIndex",
   "VM_stackWalkerMaySkipFrames",
   "VM_getStringUTF8Length",
   "VM_classInitIsFinished",
   "VM_getClassFromNewArrayType",
   "VM_getArrayClassFromComponentClass",
   "VM_matchRAMclassFromROMclass",
   "VM_getInt32FieldAt",
   "VM_getInt64FieldAt",
   "VM_setInt64FieldAt",
   "VM_compareAndSwapInt64FieldAt",
   "VM_getArrayLengthInElements",
   "VM_getClassFromJavaLangClass",
   "VM_getOffsetOfClassFromJavaLangClassField",
   "VM_getIdentityHashSaltPolicy",
   "VM_getOffsetOfJLThreadJ9Thread",
   "VM_getVFTEntry",
   "VM_scanReferenceSlotsInClassForOffset",
   "VM_findFirstHotFieldTenuredClassOffset",
   "VM_getResolvedVirtualMethod",
   "VM_getInstanceFieldOffset",
   "VM_getJavaLangClassHashCode",
   "VM_getClassDepthAndFlagsValue",
   "VM_getMethodFromName",
   "VM_getMethodFromClass",
   "VM_isClassVisible",
   "VM_markClassForTenuredAlignment",
   "VM_reportHotField",
   "VM_getReferenceSlotsInClass",
   "VM_getMethodSize",
   "VM_addressOfFirstClassStatic",
   "VM_getStaticFieldAddress",
   "VM_getInterpreterVTableSlot",
   "VM_revertToInterpreted",
   "VM_getLocationOfClassLoaderObjectPointer",
   "VM_getClassFromMethodBlock",
   "VM_fetchMethodExtendedFlagsPointer",
   "VM_stringEquals",
   "VM_getStringHashCode",
   "VM_getLineNumberForMethodAndByteCodeIndex",
   "VM_getObjectNewInstanceImplMethod",
   "VM_getBytecodePC",
   "VM_setInvokeExactJ2IThunk",
   "VM_createMethodHandleArchetypeSpecimen",
   "VM_instanceOfOrCheckCast",
   "VM_getResolvedMethodsAndMirror",
   "VM_getVMInfo",
   "VM_dereferenceStaticAddress",
   "VM_getClassFromCP",
   "VM_getROMMethodFromRAMMethod",
   "VM_getJ2IThunk",
   "VM_needsInvokeExactJ2IThunk",
   "VM_instanceOfOrCheckCastNoCacheUpdate",
   "VM_getCellSizeForSizeClass",
   "VM_getObjectSizeClass",
   "VM_stackWalkerMaySkipFramesSVM",
   "VM_getFields",
   "VM_increaseOSRGlobalBufferSize",
   "VM_methodOfDirectOrVirtualHandle",
   "VM_targetMethodFromMemberName",
   "VM_targetMethodFromMethodHandle",
   "VM_getKnotIndexOfInvokeCacheArrayAppendixElement",
   "VM_targetMethodFromInvokeCacheArrayMemberNameObj",
   "VM_refineInvokeCacheElementSymRefWithKnownObjectIndex",
   "VM_isLambdaFormGeneratedMethod",
   "VM_getMemberNameMethodInfo",
   "VM_isMethodHandleExpectedType",
   "VM_getMemberNameFieldKnotIndexFromMethodHandleKnotIndex",
   "VM_isStable",
   "VM_delegatingMethodHandleTarget",
   "VM_getVMTargetOffset",
   "VM_getVMIndexOffset",
   "VM_inSnapshotMode",
   "VM_isInvokeCacheEntryAnArray",
   "VM_getMethodHandleTableEntryIndex",
   "CompInfo_isCompiled",
   "CompInfo_getPCIfCompiled",
   "CompInfo_getInvocationCount",
   "CompInfo_setInvocationCount",
   "CompInfo_getJ9MethodExtra",
   "CompInfo_isJNINative",
   "CompInfo_isJSR292",
   "CompInfo_getMethodBytecodeSize",
   "CompInfo_setJ9MethodExtra",
   "CompInfo_setInvocationCountAtomic",
   "CompInfo_getJ9MethodStartPC",
   "ClassEnv_classFlagsValue",
   "ClassEnv_superClassesOf",
   "ClassEnv_indexedSuperClassOf",
   "ClassEnv_iTableOf",
   "ClassEnv_iTableNext",
   "ClassEnv_iTableRomClass",
   "ClassEnv_getITable",
   "ClassEnv_enumerateFields",
   "ClassEnv_flattenedArrayElementSize",
   "ClassEnv_getDefaultValueSlotAddress",
   "SharedCache_getClassChainOffsetIdentifyingLoader",
   "SharedCache_rememberClass",
   "SharedCache_addHint",
   "SharedCache_storeSharedData",
   "runFEMacro_invokeCollectHandleNumArgsToCollect",
   "runFEMacro_invokeExplicitCastHandleConvertArgs",
   "runFEMacro_targetTypeL",
   "runFEMacro_invokeILGenMacrosInvokeExactAndFixup",
   "runFEMacro_invokeArgumentMoverHandlePermuteArgs",
   "runFEMacro_invokePermuteHandlePermuteArgs",
   "runFEMacro_invokeGuardWithTestHandleNumGuardArgs",
   "runFEMacro_invokeInsertHandle",
   "runFEMacro_invokeSpreadHandleArrayArg",
   "runFEMacro_invokeSpreadHandle",
   "runFEMacro_invokeFoldHandle",
   "runFEMacro_invokeFoldHandle2",
   "runFEMacro_invokeFinallyHandle",
   "runFEMacro_invokeFilterArgumentsHandle",
   "runFEMacro_invokeFilterArgumentsHandle2",
   "runFEMacro_invokeCatchHandle",
   "runFEMacro_invokeILGenMacrosParameterCount",
   "runFEMacro_invokeILGenMacrosArrayLength",
   "runFEMacro_invokeILGenMacrosGetField",
   "runFEMacro_invokeFilterArgumentsWithCombinerHandleNumSuffixArgs",
   "runFEMacro_invokeFilterArgumentsWithCombinerHandleFilterPosition",
   "runFEMacro_invokeFilterArgumentsWithCombinerHandleArgumentIndices",
   "runFEMacro_invokeCollectHandleAllocateArray",
   "CHTable_clearReservable",
   "IProfiler_profilingSample",
   "IProfiler_searchForMethodSample",
   "IProfiler_getMaxCallCount",
   "IProfiler_setCallCount",
   "Recompilation_getJittedBodyInfoFromPC",
   "KnownObjectTable_getOrCreateIndex",
   "KnownObjectTable_getOrCreateIndexAt",
   "KnownObjectTable_getPointer",
   "KnownObjectTable_getExistingIndexAt",
   "KnownObjectTable_mutableCallSiteEpoch",
   "KnownObjectTable_dereferenceKnownObjectField",
   "KnownObjectTable_dereferenceKnownObjectField2",
   "KnownObjectTable_createSymRefWithKnownObject",
   "KnownObjectTable_getReferenceField",
   "KnownObjectTable_getKnownObjectTableDumpInfo",
   "AOTCache_getROMClassBatch",
   };

   static_assert(sizeof(messageNames) / sizeof(messageNames[0]) == MessageType_MAXTYPE,
                 "Invalid number of message type names: possibly missing a name for a newly added message");
   }; // namespace JITServer
