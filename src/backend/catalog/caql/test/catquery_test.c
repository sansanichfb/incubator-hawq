#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include "cmockery.h"

#include "c.h"
#include "postgres.h"
#include "postmaster/identity.h"
#include "catquery_mock.c"


bool
catalog_check_helper(cqContext *pCtx, HeapTuple tuple)
{
	bool ret = false;
	PG_TRY();
	{
		disable_catalog_check(pCtx, tuple);
	}
	PG_CATCH();
	{
		ret = true;
	}
	PG_END_TRY();
	return ret;
}

/*
 * Tests
 */
void
test__is_builtin_object__oid(void **state)
{
	HeapTuple ht = build_pg_class_tuple();

	HeapTupleSetOid(ht, 1000);
	assert_true(is_builtin_object(NULL, ht));

	HeapTupleSetOid(ht, 17000);
	assert_false(is_builtin_object(NULL, ht));
}

void
test__is_builtin_object__non_oid(void **state)
{
	cqContext ctx;
	ctx.cq_relationId = AttributeRelationId;
	HeapTuple ht = build_pg_attribute_tuple(1255);

	assert_true(is_builtin_object(&ctx, ht));

	ht = build_pg_attribute_tuple(17000);
	assert_false(is_builtin_object(&ctx, ht));
}

void
test__disable_catalog_check__false_role(void **state)
{
	cqContext ctx;
	HeapTuple ht;

	ctx.cq_relationId = AttributeRelationId;
	ht = build_pg_attribute_tuple(18000);

	Gp_role = GP_ROLE_DISPATCH;
	/*
	 * We don't acutally call AmIMaster() since it is bypassed by GP_ROLE_DISPATCH
	 */
	/* will_return(AmIMaster, true); */
	assert_false(catalog_check_helper(&ctx, ht));
}

void
test__disable_catalog_check__false_master(void **state)
{
	cqContext ctx;
	HeapTuple ht;

	ctx.cq_relationId = AttributeRelationId;
	ht = build_pg_attribute_tuple(18000);

	Gp_role = GP_ROLE_EXECUTE;
	will_return(AmIMaster, false);
	gp_disable_catalog_access_on_segment = false;
	assert_false(catalog_check_helper(&ctx, ht));
}

void
test__disable_catalog_check__false_access(void **state)
{
	cqContext ctx;
	HeapTuple ht;

	ctx.cq_relationId = AttributeRelationId;
	ht = build_pg_attribute_tuple(18000);

	Gp_role = GP_ROLE_EXECUTE;
	will_return(AmIMaster, true);
	gp_disable_catalog_access_on_segment = false;
	assert_false(catalog_check_helper(&ctx, ht));
}

void
test__disable_catalog_check__true(void **state)
{
	cqContext ctx;
	HeapTuple ht = build_pg_class_tuple();
	HeapTupleSetOid(ht, 18000);

	Gp_role = GP_ROLE_EXECUTE;
	will_return(AmIMaster, false);
	gp_disable_catalog_access_on_segment = true;

	assert_true(catalog_check_helper(&ctx, ht));
}

int
main(int argc, char* argv[])
{
	cmockery_parse_arguments(argc, argv);
	const UnitTest tests[] =
	{
		unit_test(test__is_builtin_object__oid),
		unit_test(test__is_builtin_object__non_oid),
		unit_test(test__disable_catalog_check__false_role),
		unit_test(test__disable_catalog_check__false_master),
		unit_test(test__disable_catalog_check__false_access),
		unit_test(test__disable_catalog_check__true)
	};
	
	return run_tests(tests);
}

