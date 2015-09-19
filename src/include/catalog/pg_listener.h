/*-------------------------------------------------------------------------
 *
 * pg_listener.h
 *	  Asynchronous notification
 *
 *
 * Portions Copyright (c) 1996-2008, PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 * $PostgreSQL: pgsql/src/include/catalog/pg_listener.h,v 1.21 2006/03/05 15:58:54 momjian Exp $
 *
 * NOTES
 *	  the genbki.sh script reads this file and generates .bki
 *	  information from the DATA() statements.
 *
 *-------------------------------------------------------------------------
 */
#ifndef PG_LISTENER_H
#define PG_LISTENER_H

#include "catalog/genbki.h"

/* TIDYCAT_BEGINDEF

   CREATE TABLE pg_listener
   with (shared=false, oid=false, relid=2614, content=MASTER_ONLY)
   (
   relname       name    ,
   listenerpid   integer ,
   notification  integer 
   );


   TIDYCAT_ENDDEF
*/

/* TIDYCAT_BEGIN_CODEGEN 

   WARNING: DO NOT MODIFY THE FOLLOWING SECTION: 
   Generated by tidycat.pl version 21.
   on Wed Nov 24 14:20:19 2010
*/


/*
 TidyCat Comments for pg_listener:
  Table does not have an Oid column.
  Table does not have static type (only legal for pre-3.3 tables). 
  Table contents are only maintained on MASTER.

*/

/* ----------------
 *		pg_listener definition.  cpp turns this into
 *		typedef struct FormData_pg_listener
 * ----------------
 */
#define ListenerRelationId	2614

CATALOG(pg_listener,2614) BKI_WITHOUT_OIDS
{
	NameData	relname;		
	int4		listenerpid;	
	int4		notification;	
} FormData_pg_listener;


/* ----------------
 *		Form_pg_listener corresponds to a pointer to a tuple with
 *		the format of pg_listener relation.
 * ----------------
 */
typedef FormData_pg_listener *Form_pg_listener;


/* ----------------
 *		compiler constants for pg_listener
 * ----------------
 */
#define Natts_pg_listener				3
#define Anum_pg_listener_relname		1
#define Anum_pg_listener_listenerpid	2
#define Anum_pg_listener_notification	3


/* TIDYCAT_END_CODEGEN */

/* ----------------
 *		initial contents of pg_listener are NOTHING.
 * ----------------
 */

#endif   /* PG_LISTENER_H */
