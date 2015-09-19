#ifndef PG_REMOTE_CREDENTIALS_H
#define PG_REMOTE_CREDENTIALS_H

#include "catalog/genbki.h"

/* TIDYCAT_BEGINDEF

   CREATE TABLE pg_remote_credentials
   with (relid=7076, reltype_oid=7077, toast_oid=7078, toast_index=7079, toast_reltype=7080, camelcase=RemoteCredentials, oid=false, shared=false)
   (
   rcowner			oid, 
   rcservice		text, 
   rcremoteuser		text,
   rcremotepassword	text
   );

   create unique index on pg_remote_credentials(rcowner, rcservice) with (indexid=7081, indexname=pg_remote_credentials_owner_service_index, CamelCase=RemoteCredentialsOwnerService);

   alter table pg_remote_credentials add fk rcowner on pg_authid(oid);

   TIDYCAT_ENDDEF
*/
/* TIDYCAT_BEGIN_CODEGEN 

   WARNING: DO NOT MODIFY THE FOLLOWING SECTION: 
   Generated by ./tidycat.pl version 34
   on Wed Feb  5 22:00:04 2014
*/


/*
 TidyCat Comments for pg_remote_credentials:
  Table does not have an Oid column.
  Table has static type (see pg_types.h).
  Table has TOASTable columns, and TOAST table has static type.

*/

/* ----------------
 *		pg_remote_credentials definition.  cpp turns this into
 *		typedef struct FormData_pg_remote_credentials
 * ----------------
 */
#define RemoteCredentialsRelationId	7076

CATALOG(pg_remote_credentials,7076) BKI_WITHOUT_OIDS
{
	Oid		rcowner;			
	text	rcservice;			
	text	rcremoteuser;		
	text	rcremotepassword;	
} FormData_pg_remote_credentials;


/* ----------------
 *		Form_pg_remote_credentials corresponds to a pointer to a tuple with
 *		the format of pg_remote_credentials relation.
 * ----------------
 */
typedef FormData_pg_remote_credentials *Form_pg_remote_credentials;


/* ----------------
 *		compiler constants for pg_remote_credentials
 * ----------------
 */
#define Natts_pg_remote_credentials					4
#define Anum_pg_remote_credentials_rcowner			1
#define Anum_pg_remote_credentials_rcservice		2
#define Anum_pg_remote_credentials_rcremoteuser		3
#define Anum_pg_remote_credentials_rcremotepassword	4


/* TIDYCAT_END_CODEGEN */

#endif	/* PG_REMOTE_CREDENTIALS_H */
