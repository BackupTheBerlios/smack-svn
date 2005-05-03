Summary: A Sample free drum synth
Name: smack
Version: 0.0.2
Release: 1
License: GPL
Group: Applications/Multimedia
URL: http://smack.berlios.de
Source0: %{name}-%{version}.tar.gz
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-buildroot
Requires: gtk2 om omins swh-plugins blop cmt liblo phat
BuildPrereq: gtk2-devel liblo-devel phat-devel

%description
Smack is a drum synth, 100 percent sample free. It intends to emulate a large number of famous drum machines (TR/others) as well as physical modeling of hand drums. It's built with LADSPA plugins and the Om modular synth.

%prep
%setup -q

%build
%configure
make

%makeinstall

%clean
rm -rf %{buildroot}

%files
%defattr(-,root,root,-)
%{_bindir}/smack
%dir %{_datadir}/smack
%{_datadir}/smack/pixmaps/*.png
%{_datadir}/smack/om/smack808/*.om
%{_datadir}/smack/om/smack909/*.om
%{_datadir}/smack/om/smackfm/*.om
%{_datadir}/smack/om/supersmack/*.om
%doc AUTHORS ChangeLog COPYING NEWS README TODO


%changelog
* Tue Apr 26 2005 Loki Davison <loki@berlios.de>
- initial package, v0.0.2

