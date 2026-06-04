/*[INCLUDE-IF JAVA_SPEC_VERSION >= 17]*/
/*
 * Copyright IBM Corp. and others 1998
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
 */
package java.lang;

/*[IF JAVA_SPEC_VERSION >= 25]*/
import java.lang.classfile.*;
import java.lang.classfile.attribute.SyntheticAttribute;
import java.lang.constant.ClassDesc;
import java.lang.constant.MethodTypeDesc;
/*[ELSE] JAVA_SPEC_VERSION >= 25 */
import jdk.internal.org.objectweb.asm.*;
/*[ENDIF] JAVA_SPEC_VERSION >= 25 */

import java.util.ArrayList;
import java.util.List;

/*[IF JAVA_SPEC_VERSION >= 25]*/
import static java.lang.classfile.ClassFile.*;
/*[ENDIF] JAVA_SPEC_VERSION >= 25 */

final class JFRClassTransformer {

	private static final String EVENT_HANDLER_FIELD = "eventHandler";
	private static final String START_TIME_FIELD = "startTime";
	private static final String DURATION_FIELD = "duration";
/*[IF JAVA_SPEC_VERSION >= 25]*/
	private static final ClassDesc OBJECT_DESC = ClassDesc.of("java.lang.Object");
	private static final ClassDesc LONG_DESC = ClassDesc.of("long");
/*[ELSE] JAVA_SPEC_VERSION >= 25 */
	private static final String OBJECT_DESC = "Ljava/lang/Object;";
	private static final String LONG_DESC = "J";
/*[ENDIF] JAVA_SPEC_VERSION >= 25 */

	private static class FieldDescriptor {
		public final String name;
/*[IF JAVA_SPEC_VERSION >= 25]*/
		public final ClassDesc descriptor;
/*[ELSE] JAVA_SPEC_VERSION >= 25 */
		public final String descriptor;
/*[ENDIF] JAVA_SPEC_VERSION >= 25 */
		public final int access;

		public FieldDescriptor(
				String name,
/*[IF JAVA_SPEC_VERSION >= 25]*/
				ClassDesc descriptor,
/*[ELSE] JAVA_SPEC_VERSION >= 25 */
				String descriptor,
/*[ENDIF] JAVA_SPEC_VERSION >= 25 */
				int access) {
			this.name = name;
			this.descriptor = descriptor;
			this.access = access;
		}

		public static FieldDescriptor staticField(
				String name,
/*[IF JAVA_SPEC_VERSION >= 25]*/
				ClassDesc descriptor
/*[ELSE] JAVA_SPEC_VERSION >= 25 */
				String descriptor
/*[ENDIF] JAVA_SPEC_VERSION >= 25 */
				) {
			return new FieldDescriptor(
					name, descriptor,
/*[IF JAVA_SPEC_VERSION >= 25]*/
					ACC_PRIVATE | ACC_STATIC | ACC_SYNTHETIC
/*[ELSE] JAVA_SPEC_VERSION >= 25 */
					Opcodes.ACC_PRIVATE | Opcodes.ACC_STATIC | Opcodes.ACC_SYNTHETIC
/*[ENDIF] JAVA_SPEC_VERSION >= 25 */
					);
		}

		public static FieldDescriptor transientField(
				String name,
/*[IF JAVA_SPEC_VERSION >= 25]*/
				ClassDesc descriptor
/*[ELSE] JAVA_SPEC_VERSION >= 25 */
				String descriptor
/*[ENDIF] JAVA_SPEC_VERSION >= 25 */
				) {
			return new FieldDescriptor(
					name, descriptor,
/*[IF JAVA_SPEC_VERSION >= 25]*/
					ACC_PRIVATE | ACC_TRANSIENT | ACC_SYNTHETIC
/*[ELSE] JAVA_SPEC_VERSION >= 25 */
					Opcodes.ACC_PRIVATE | Opcodes.ACC_TRANSIENT | Opcodes.ACC_SYNTHETIC
/*[ENDIF] JAVA_SPEC_VERSION >= 25 */
					);
		}

		public static FieldDescriptor instanceField(
				String name,
/*[IF JAVA_SPEC_VERSION >= 25]*/
				ClassDesc descriptor
/*[ELSE] JAVA_SPEC_VERSION >= 25 */
				String descriptor
/*[ENDIF] JAVA_SPEC_VERSION >= 25 */
				) {
			return new FieldDescriptor(
					name, descriptor,
/*[IF JAVA_SPEC_VERSION >= 25]*/
					ACC_PRIVATE | ACC_SYNTHETIC
/*[ELSE] JAVA_SPEC_VERSION >= 25 */
					Opcodes.ACC_PRIVATE | Opcodes.ACC_SYNTHETIC
/*[ENDIF] JAVA_SPEC_VERSION >= 25 */
					);
		}
	}

	private static class MethodDescriptor {
		public final String name;
/*[IF JAVA_SPEC_VERSION >= 25]*/
		public final MethodTypeDesc descriptor;
/*[ELSE] JAVA_SPEC_VERSION >= 25 */
		public final String descriptor;
/*[ENDIF] JAVA_SPEC_VERSION >= 25 */
		public final int access;
		public final MethodGenerator generator;

		public MethodDescriptor(
				String name,
/*[IF JAVA_SPEC_VERSION >= 25]*/
				MethodTypeDesc descriptor,
/*[ELSE] JAVA_SPEC_VERSION >= 25 */
				String descriptor,
/*[ENDIF] JAVA_SPEC_VERSION >= 25 */
				int access, MethodGenerator generator) {
				this.name = name;
				this.descriptor = descriptor;
				this.access = access;
				this.generator = generator;
		}

		public static MethodDescriptor publicMethod(
				String name,
/*[IF JAVA_SPEC_VERSION >= 25]*/
				MethodTypeDesc descriptor,
/*[ELSE] JAVA_SPEC_VERSION >= 25 */
				String descriptor,
/*[ENDIF] JAVA_SPEC_VERSION >= 25 */
				MethodGenerator generator) {
				return new MethodDescriptor(
						name, descriptor,
/*[IF JAVA_SPEC_VERSION >= 25]*/
						ACC_PUBLIC,
/*[ELSE] JAVA_SPEC_VERSION >= 25 */
						Opcodes.ACC_PUBLIC,
/*[ENDIF] JAVA_SPEC_VERSION >= 25 */
						generator);
		}
	}

	@FunctionalInterface
	private interface MethodGenerator {
		void generate(
/*[IF JAVA_SPEC_VERSION >= 25]*/
				CodeBuilder cb
/*[ELSE] JAVA_SPEC_VERSION >= 25 */
				MethodVisitor mv
/*[ENDIF] JAVA_SPEC_VERSION >= 25 */
				);
	}

	private static byte[] addFieldsAndMethods(byte[] classBytes, List<FieldDescriptor> fields,
			List<MethodDescriptor> methods) {
/*[IF JAVA_SPEC_VERSION >= 25]*/
		ClassFile cf = ClassFile.of();

		return cf.transformClass(cf.parse(classBytes), (classBuilder, classElement) -> {
			classBuilder.accept(classElement);
			if (classElement instanceof ClassFileVersion) {
				for (FieldDescriptor field : fields) {
					classBuilder.withField(field.name, field.descriptor, fb -> {
						fb.withFlags(field.access);
						if ((field.access & ACC_SYNTHETIC) != 0) {
							fb.with(SyntheticAttribute.of());
						}
					});
				}

				for (MethodDescriptor method : methods) {
					classBuilder.withMethod(method.name, method.descriptor, method.access, mb -> {
						mb.withCode(method.generator::generate);
					});
				}
			}
		});
/*[ELSE] JAVA_SPEC_VERSION >= 25 */
		ClassReader reader = new ClassReader(classBytes);
		ClassWriter writer = new ClassWriter(reader, ClassWriter.COMPUTE_MAXS);

		ClassVisitor visitor = new ClassVisitor(Opcodes.ASM7, writer) {
			@Override
			public void visitEnd() {
				for (FieldDescriptor field : fields) {
					FieldVisitor fv = super.visitField(field.access, field.name, field.descriptor, null, null);
					if (fv != null) {
						fv.visitEnd();
					}
				}

				for (MethodDescriptor method : methods) {
					MethodVisitor mv = super.visitMethod(method.access, method.name, method.descriptor, null, null);
					if (mv != null) {
						mv.visitCode();
						method.generator.generate(mv);
						mv.visitEnd();
					}
				}

				super.visitEnd();
			}
		};

		reader.accept(visitor, 0);
		return writer.toByteArray();
/*[ENDIF] JAVA_SPEC_VERSION >= 25 */
	}

	/**
	 * Transforms the class bytes to add the JFR event handler fields and methods.
	 * Adding methods is optional and depends on the super class of the class being
	 * transformed.
	 *
	 * @param classBytes the class bytes to transform
	 * @param addMethods whether to add the JFR event handler methods
	 * @return the transformed class bytes
	 */
	static byte[] transformClass(byte[] classBytes, boolean addMethods) {
		List<FieldDescriptor> fields = new ArrayList<>();

		fields.add(FieldDescriptor.staticField(EVENT_HANDLER_FIELD, OBJECT_DESC));

		fields.add(FieldDescriptor.transientField(START_TIME_FIELD, LONG_DESC));

		fields.add(FieldDescriptor.transientField(DURATION_FIELD, LONG_DESC));

		List<MethodDescriptor> methods = new ArrayList<>();

		if (addMethods) {
			methods.add(
				MethodDescriptor.publicMethod(
					"isEnabled",
/*[IF JAVA_SPEC_VERSION >= 25]*/
					MethodTypeDesc.of(ClassDesc.of("boolean")), cb -> {
						cb.iconst_0();
						cb.ireturn();
/*[ELSE] JAVA_SPEC_VERSION >= 25 */
				"()Z", mv -> {
					mv.visitInsn(Opcodes.ICONST_0);
					mv.visitInsn(Opcodes.IRETURN);
					mv.visitMaxs(1, 1);
/*[ENDIF] JAVA_SPEC_VERSION >= 25 */
			}));

			methods.add(
				MethodDescriptor.publicMethod(
					"shouldCommit",
/*[IF JAVA_SPEC_VERSION >= 25]*/
					MethodTypeDesc.of(ClassDesc.of("boolean")), cb -> {
						cb.iconst_0();
						cb.ireturn();
/*[ELSE] JAVA_SPEC_VERSION >= 25 */
				"()Z", mv -> {
					mv.visitInsn(Opcodes.ICONST_0);
					mv.visitInsn(Opcodes.IRETURN);
					mv.visitMaxs(1, 1);
/*[ENDIF] JAVA_SPEC_VERSION >= 25 */
			}));

			methods.add(
				MethodDescriptor.publicMethod(
					"commit",
/*[IF JAVA_SPEC_VERSION >= 25]*/
					MethodTypeDesc.of(ClassDesc.of("void")), cb -> {
						cb.return_();
/*[ELSE] JAVA_SPEC_VERSION >= 25 */
				"()V", mv -> {
					mv.visitInsn(Opcodes.RETURN);
					mv.visitMaxs(0, 1);
/*[ENDIF] JAVA_SPEC_VERSION >= 25 */
			}));

			methods.add(
				MethodDescriptor.publicMethod(
					"end",
/*[IF JAVA_SPEC_VERSION >= 25]*/
					MethodTypeDesc.of(ClassDesc.of("void")), cb -> {
						cb.return_();
/*[ELSE] JAVA_SPEC_VERSION >= 25 */
				"()V", mv -> {
					mv.visitInsn(Opcodes.RETURN);
					mv.visitMaxs(0, 1);
/*[ENDIF] JAVA_SPEC_VERSION >= 25 */
			}));

			methods.add(
				MethodDescriptor.publicMethod(
					"begin",
/*[IF JAVA_SPEC_VERSION >= 25]*/
					MethodTypeDesc.of(ClassDesc.of("void")), cb -> {
						cb.return_();
/*[ELSE] JAVA_SPEC_VERSION >= 25 */
				"()V", mv -> {
					mv.visitInsn(Opcodes.RETURN);
					mv.visitMaxs(0, 1);
/*[ENDIF] JAVA_SPEC_VERSION >= 25 */
			}));
		}

		return addFieldsAndMethods(classBytes, fields, methods);
	}
}
