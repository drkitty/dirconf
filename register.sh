vim() {
	/usr/bin/env vim --cmd "let localrtp = '`findup .vim`'" -u ~/.vimrc $*
}
