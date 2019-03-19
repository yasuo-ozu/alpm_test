#include <stdio.h>
#include <stdlib.h>
#include <alpm.h>
#include <alpm_list.h>

void print_alpm_info(void) {
	alpm_errno_t err = ALPM_ERR_OK;
	printf("alpm version = %s\n", alpm_version());

	int cap = alpm_capabilities();
	if (err) {
		fprintf(stderr, "alpm_capabilities: %s\n", alpm_strerror(err));
		exit(1);
	}

	printf("alpm capabilities =");
	if (cap & ALPM_CAPABILITY_NLS) printf(" nls");
	if (cap & ALPM_CAPABILITY_DOWNLOADER) printf(" downloader");
	if (cap & ALPM_CAPABILITY_SIGNATURES) printf(" signatures");
	printf("\n");
}

void print_alpm_state(alpm_handle_t *handle) {
	alpm_list_t *lp = NULL;
	printf("root = %s\n", alpm_option_get_root(handle));
	printf("dbpath = %s\n", alpm_option_get_dbpath(handle));
	printf("lockfile = %s\n", alpm_option_get_lockfile(handle));
	printf("logfile = %s\n", alpm_option_get_logfile(handle));
	printf("gpgdir = %s\n", alpm_option_get_gpgdir(handle));
	printf("usesyslog = %s\n", alpm_option_get_usesyslog(handle) ? "TRUE" : "FALSE");
	printf("arch = %s\n", alpm_option_get_arch(handle));
	printf("deltaratio = %lf\n", alpm_option_get_deltaratio(handle));
	printf("checkspace = %s\n", alpm_option_get_checkspace(handle) ? "TRUE" : "FALSE");
	printf("dbext = %s\n", alpm_option_get_dbext(handle));
	printf("default siglevel = %d\n", alpm_option_get_default_siglevel(handle));
	printf("local file siglevel = %d\n", alpm_option_get_local_file_siglevel(handle));
	printf("remote file siglevel = %d\n", alpm_option_get_remote_file_siglevel(handle));
	
	printf("cachedirs =");
	lp = alpm_option_get_cachedirs(handle);
	while (lp != NULL) {
		printf(" %s", (char *) lp->data);
		lp = alpm_list_next(lp);
	}
	printf("\n");

	printf("hookdirs =");
	lp = alpm_option_get_hookdirs(handle);
	while (lp != NULL) {
		printf(" %s", (char *) lp->data);
		lp = alpm_list_next(lp);
	}
	printf("\n");

	printf("overwrite_files =");
	lp = alpm_option_get_overwrite_files(handle);
	while (lp != NULL) {
		printf(" %s", (char *) lp->data);
		lp = alpm_list_next(lp);
	}
	printf("\n");

	printf("noupgrades =");
	lp = alpm_option_get_noupgrades(handle);
	while (lp != NULL) {
		printf(" %s", (char *) lp->data);
		lp = alpm_list_next(lp);
	}
	printf("\n");

	printf("noextracts =");
	lp = alpm_option_get_noextracts(handle);
	while (lp != NULL) {
		printf(" %s", (char *) lp->data);
		lp = alpm_list_next(lp);
	}
	printf("\n");

	printf("ignorepkgs =");
	lp = alpm_option_get_ignorepkgs(handle);
	while (lp != NULL) {
		printf(" %s", (char *) lp->data);
		lp = alpm_list_next(lp);
	}
	printf("\n");

	printf("ignoregroups =");
	lp = alpm_option_get_ignoregroups(handle);
	while (lp != NULL) {
		printf(" %s", (char *) lp->data);
		lp = alpm_list_next(lp);
	}
	printf("\n");

	printf("assymeinstalled =");
	lp = alpm_option_get_assumeinstalled(handle);
	while (lp != NULL) {
		printf(" %s", (char *) lp->data);
		lp = alpm_list_next(lp);
	}
	printf("\n");
}

void print_dbinfo(alpm_db_t *db) {
	alpm_list_t *lp;
	if (db == NULL) return;
	printf("[%s]\n", alpm_db_get_name(db));
	printf("  siglevel = %d\n", alpm_db_get_siglevel(db));
	printf("  valid = %s\n", alpm_db_get_valid(db) == 0 ? "valid" : "invalid"); // invalid : -1
	printf("  servers =");
	lp = alpm_db_get_servers(db);
	while (lp != NULL) {
		printf(" %s", (char *) lp->data);
		lp = alpm_list_next(lp);
	}
	printf("\n");
		
	
}

int main(void) {
	alpm_list_t *lp;
	alpm_errno_t err = ALPM_ERR_OK;
	
	printf("# alpm info:\n");
	print_alpm_info();

	alpm_handle_t *handle = alpm_initialize("/", "/var/lib/pacman", &err);
	if (err) {
		fprintf(stderr, "alpm_initialize: %s\n", alpm_strerror(err));
		return 1;
	}
	
	printf("# alpm state:\n");
	print_alpm_state(handle);
	
	alpm_db_t *localdb = alpm_get_localdb(handle);
	alpm_list_t *syncdbs = alpm_get_syncdbs(handle);
	
	printf("# local db:\n");
	print_dbinfo(localdb);
	printf("# sync dbs:\n");
	lp = syncdbs;
	while (lp != NULL) {
		print_dbinfo((alpm_db_t *) lp->data);
		lp = alpm_list_next(lp);
	}
	printf("\n");
	
}
