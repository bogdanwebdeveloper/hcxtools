#define HCX_EAPOL_TIMEOUT		1
#define HCX_NC				2
#define HCX_IE				3
#define HCX_ESSIDS			4
#define HCX_PMKIDEAPOLHC_OUT		'o'
#define HCX_PMKIDEAPOLJTR_OUT		'j'
#define HCX_HELP			'h'
#define HCX_VERSION			'v'

#define ESSID_LEN_MAX		32
#define RSN_LEN_MIN		20
#define WPA_LEN_MIN		22
#define	OPTIONLEN_MAX		1024

#define MACLIST_MAX		100000
#define HANDSHAKELIST_MAX	100000
#define PMKIDLIST_MAX		100000
#define MESSAGELIST_MAX		16

#define ESSIDSMAX		1

#define EAPOLTIMEOUT		200000
#define NONCEERRORCORRECTION	0

#define HCX_TYPE_PMKID		1
#define HCX_TYPE_EAPOL		2

/*===========================================================================*/
/*===========================================================================*/
struct tags_s
{
 uint8_t	channel;
 uint8_t	kdversion;
 uint8_t	akm;
 uint8_t	groupcipher;
 uint8_t	cipher;
 uint8_t	pmkid[16];
 uint8_t	essidlen;
 uint8_t	essid[ESSID_LEN_MAX];
};
typedef struct tags_s tags_t;
#define	TAGS_SIZE (sizeof(tags_t))

/*===========================================================================*/
struct maclist_s
{
 uint64_t		timestamp;
 int			count;
 uint8_t		type;
#define	CLIENT		1
#define	AP		2
 uint8_t		status;
#define ST_PROBE_REQ	1
#define ST_BEACON	2
#define ST_PROBE_RESP	4
#define ST_ASSOC_REQ	8
#define ST_REASSOC_REQ	16
 uint8_t		addr[6];
 uint8_t		kdversion;
 uint8_t		groupcipher;
 uint8_t		cipher;
 uint8_t		akm;
#define	WPA1		1
#define WPA2		2
#define WPA2kv3		4
 uint8_t		algorithm;
 uint8_t		essidlen;
 uint8_t		essid[ESSID_LEN_MAX];
};
typedef struct maclist_s maclist_t;
#define	MACLIST_SIZE (sizeof(maclist_t))

static int sort_maclist_by_mac(const void *a, const void *b)
{
const maclist_t *ia = (const maclist_t *)a;
const maclist_t *ib = (const maclist_t *)b;
if(ia->type > ib->type) return 1;
else if(ia->type < ib->type) return -1;
if(memcmp(ia->addr, ib->addr, 6) > 0) return 1;
else if(memcmp(ia->addr, ib->addr, 6) < 0) return -1;
if(ia->essidlen < ib->essidlen) return 1;
else if(ia->essidlen > ib->essidlen) return -1;
if(memcmp(ia->essid, ib->essid, ib->essidlen) < 0) return 1;
else if(memcmp(ia->essid, ib->essid, ib->essidlen) > 0) return -1;
return 0;
}

static int sort_maclist_by_mac_count(const void *a, const void *b)
{
const maclist_t *ia = (const maclist_t *)a;
const maclist_t *ib = (const maclist_t *)b;
if(ia->type > ib->type) return 1;
else if(ia->type < ib->type) return -1;
if(memcmp(ia->addr, ib->addr, 6) > 0) return 1;
else if(memcmp(ia->addr, ib->addr, 6) < 0) return -1;
if(ia->count < ib->count) return 1;
else if(ia->count > ib->count) return -1;
if(ia->essidlen < ib->essidlen) return 1;
else if(ia->essidlen > ib->essidlen) return -1;
if(memcmp(ia->essid, ib->essid, ib->essidlen) < 0) return 1;
else if(memcmp(ia->essid, ib->essid, ib->essidlen) > 0) return -1;
return 0;
}
/*===========================================================================*/
struct messagelist_s
{
 uint64_t		timestamp;
 uint64_t		epcount;
 uint8_t		status;
#define	ST_NC		1
 uint8_t		ap[6];
 uint8_t		client[6];
 uint8_t		message;
#define HS_M1		1
#define HS_M2		2
#define HS_M3		4
#define HS_M4		8
#define HS_PMKID	16
 unsigned long long int	rc;
 uint8_t		nonce[32];
 uint8_t		pmkid[16];
 uint16_t		eapauthlen;
 uint8_t		eapol[256];
};
typedef struct messagelist_s messagelist_t;
#define	MESSAGELIST_SIZE (sizeof(messagelist_t))

static int sort_messagelist_by_epcount(const void *a, const void *b)
{
const messagelist_t *ia = (const messagelist_t *)a;
const messagelist_t *ib = (const messagelist_t *)b;
return (ia->epcount < ib->epcount);
}
/*===========================================================================*/
struct handshakelist_s
{
 uint64_t		timestampgap;
 uint8_t		messageap;
 uint8_t		messageclient;
 unsigned long long int	rcgap;
 uint8_t		nc;
 uint8_t		ap[6];
 uint8_t		client[6];
 uint8_t		anonce[32];
 uint8_t		pmkid[16];
 uint16_t		eapauthlen;
 uint8_t		eapol[256];
};
typedef struct handshakelist_s handshakelist_t;
#define	HANDSHAKELIST_SIZE (sizeof(handshakelist_t))

static int sort_handshakelist_by_mac(const void *a, const void *b)
{
const handshakelist_t *ia = (const handshakelist_t *)a;
const handshakelist_t *ib = (const handshakelist_t *)b;

if(memcmp(ia->ap, ib->ap, 6) > 0) return 1;
else if(memcmp(ia->ap, ib->ap, 6) < 0) return -1;
if(memcmp(ia->client, ib->client, 6) > 0) return 1;
else if(memcmp(ia->client, ib->client, 6) < 0) return -1;
if(memcmp(ia->anonce, ib->anonce, 32) > 0) return 1;
else if(memcmp(ia->anonce, ib->anonce, 6) < 0) return -1;
if(ia->eapauthlen > ib->eapauthlen) return 1;
else if(ia->eapauthlen < ib->eapauthlen) return -1;
if(memcmp(ia->eapol, ib->eapol, ib->eapauthlen) > 0) return 1;
else if(memcmp(ia->eapol, ib->eapol, ib->eapauthlen) < 0) return -1;
if(ia->timestampgap > ib->timestampgap) return 1;
else if(ia->timestampgap < ib->timestampgap) return -1;
if(ia->rcgap > ib->rcgap) return 1;
else if(ia->rcgap < ib->rcgap) return -1;
return 0;
}
static int sort_handshakelist_by_timegap(const void *a, const void *b)
{
const handshakelist_t *ia = (const handshakelist_t *)a;
const handshakelist_t *ib = (const handshakelist_t *)b;

if(memcmp(ia->ap, ib->ap, 6) > 0) return 1;
else if(memcmp(ia->ap, ib->ap, 6) < 0) return -1;
if(memcmp(ia->client, ib->client, 6) > 0) return 1;
else if(memcmp(ia->client, ib->client, 6) < 0) return -1;
if(ia->timestampgap > ib->timestampgap) return 1;
else if(ia->timestampgap < ib->timestampgap) return -1;
if(ia->rcgap > ib->rcgap) return 1;
else if(ia->rcgap < ib->rcgap) return -1;
return 0;
}

/*===========================================================================*/
/*===========================================================================*/
struct pmkidlist_s
{
 uint64_t		timestamp;
 uint8_t		ap[6];
 uint8_t		client[6];
 uint8_t		anonce[32];
 uint8_t		pmkid[16];
};
typedef struct pmkidlist_s pmkidlist_t;
#define	PMKIDLIST_SIZE (sizeof(pmkidlist_t))

static int sort_pmkidlist_by_mac(const void *a, const void *b)
{
const pmkidlist_t *ia = (const pmkidlist_t *)a;
const pmkidlist_t *ib = (const pmkidlist_t *)b;

if(memcmp(ia->ap, ib->ap, 6) > 0) return 1;
else if(memcmp(ia->ap, ib->ap, 6) < 0) return -1;
if(memcmp(ia->client, ib->client, 6) > 0) return 1;
else if(memcmp(ia->client, ib->client, 6) < 0) return -1;
if(memcmp(ia->pmkid, ib->pmkid, 6) < 0) return 1;
else if(memcmp(ia->pmkid, ib->pmkid, 6) > 0) return -1;

return 0;
}
/*===========================================================================*/


