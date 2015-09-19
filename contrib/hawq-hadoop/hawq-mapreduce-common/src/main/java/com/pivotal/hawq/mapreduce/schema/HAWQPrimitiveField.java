package com.pivotal.hawq.mapreduce.schema;

/**
 * Represent a primitive field in HAWQ's schema.
 * See PrimitiveType for all primitive types.
 */
public class HAWQPrimitiveField extends HAWQField {

	/**
	 * Enumeration of all supported primitive type.
	 * Note that CHAR and BPCHAR are the same, we include BPCHAR for internal usage.
	 */
	public static enum PrimitiveType {
		BOOL, BIT, VARBIT, BYTEA, INT2, INT4, INT8, FLOAT4, FLOAT8, NUMERIC,
		CHAR, BPCHAR, VARCHAR, TEXT, DATE, TIME, TIMETZ, TIMESTAMP, TIMESTAMPTZ, INTERVAL,
		POINT, LSEG, BOX, CIRCLE, PATH, POLYGON, MACADDR, INET, CIDR, XML
	}

	private PrimitiveType type;

	/**
	 * Constructor for HAWQPrimitiveField.
	 *
	 * <p>Instead of using this constructor, we recommend you to use
	 * factory methods defined in HAWQSchema:</p>
	 *
	 * <ul>
	 *     <li>HAWQSchema.required_field(...)</li>
	 *     <li>HAWQSchema.optional_field(...)</li>
	 *     <li>HAWQSchema.required_field_array(...)</li>
	 *     <li>HAWQSchema.optional_field_array(...)</li>
	 * </ul>
	 *
	 * @param isOptional whether the field is optional or not
	 * @param name name of the field
	 * @param type type of the field
	 * @param isArray whether the field is an array
	 */
	public HAWQPrimitiveField(boolean isOptional, String name, PrimitiveType type, boolean isArray) {
		super(isOptional, name, isArray);
		// use BPCHAR internally
		if (type == PrimitiveType.CHAR) {
			type = PrimitiveType.BPCHAR;
		}
		this.type = type;
	}

	@Override
	protected boolean equalsField(HAWQField other) {
		if (other.isPrimitive()) {
			HAWQPrimitiveField p = other.asPrimitive();
			return  this.isOptional() == p.isOptional() &&
					this.getType() == p.getType() &&
					this.isArray() == p.isArray() &&
					this.getName().equals(p.getName());
		}
		return false;
	}

	@Override
	public boolean isPrimitive() {
		return true;
	}

	/**
	 * Get field's type.
	 * @return field's type
	 */
	public PrimitiveType getType() {
		return type;
	}

	@Override
	public void writeToStringBuilder(StringBuilder sb, String indent) {
		sb.append(indent)
				.append(isOptional() ? "optional " : "required ")
				.append(getType().toString().toLowerCase())
				.append(isArray() ? "[] " : " ")
				.append(getName())
				.append(";");
	}

	@Override
	public String toString() {
		StringBuilder sb = new StringBuilder("HAWQPrimitiveField { ");
		this.writeToStringBuilder(sb, "");
		sb.append(" }");
		return sb.toString();
	}
}
