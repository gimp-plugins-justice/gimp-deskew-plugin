
# config file for PRAT (see http://www.cubewano.org/prat/)

PROJ_NAME = 'gimp-deskew-plugin'

REPO_BASE = 'https://svn.cubewano.org/repos/%(PROJ_NAME)s'%locals()

REPO_TRUNK = '%(REPO_BASE)s/trunk'%locals()
REPO_TAG_DIR = '%(REPO_BASE)s/tags'%locals()

RELEASES_DIR = '/srv/cubewano/www/%(PROJ_NAME)s/downloads'%locals()

# DOC_OUTPUT = '/home/quarl/proj/%(PROJ_NAME)s/www/releases.htxt'%locals()
# DOC_URL_DOWNLOAD_PREFIX = 'releases/'
