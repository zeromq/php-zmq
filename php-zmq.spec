# Define version and release number
%global version 0.6.0

# Temporarily using git checkout since the release version won't build anymore.
%global release 4.20120613git516bd6f

Name:          php-zmq
Version:       %{version}
Release:       %{release}%{?dist}
Summary:       PHP 0MQ/zmq/zeromq extension
# run-tests.php is PHP.  Everything else is BSD
License:       BSD and PHP
Group:         Development/Libraries
URL:           http://github.com/mkoppanen/php-zmq
Source:        php-zmq-0.6.0-2.20120613git516bd6f.tar.gz

BuildRequires: php-devel
BuildRequires: php-cli
BuildRequires: zeromq-devel >= 2.0.7

Requires:      zeromq >= 2.0.7

%filter_from_provides /^zmq.so/d
%filter_setup

%description
PHP extension for the 0MQ/zmq/zeromq messaging system

%prep
%setup -q -n php-zmq

%build
/usr/bin/phpize
%configure
%{__make} %{?_smp_mflags}

%install
%{__make} install INSTALL_ROOT=%{buildroot}

# Create the ini location
%{__mkdir} -p %{buildroot}/%{_sysconfdir}/php.d

# Preliminary extension ini
echo "extension=zmq.so" > %{buildroot}/%{_sysconfdir}/php.d/zmq.ini

%check
echo "n" | make test

%files
%doc README LICENSE
%{_libdir}/php/modules/zmq.so
%config(noreplace) %{_sysconfdir}/php.d/zmq.ini

%changelog
* Thu Jun 14 2012 Ralph Bean <rbean@redhat.com> - 0.6.0-4.20120613git516bd6f
 - Fixed the private-shared-object-provides for reals with John Ciesla's help.
* Wed Jun 13 2012 Ralph Bean <rbean@redhat.com> - 0.6.0-3.20120613git516bd6f
 - Updated License to BSD and PHP.
 - Removed spurious gcc BuildRequires.
 - Fixed private-shared-object-provides.
* Wed Jun 13 2012 Ralph Bean <rbean@redhat.com> - 0.6.0-2.20120613git516bd6f
 - Using tarball of git checkout since the 0.6.0 release won't build anymore.
 - Using valid shortname for BSD license.
 - Added README and LICENSE to the doc
 - Use %%global instead of %%define.
 - Changed 0MQ to 0MQ/zmq/zeromq in Summary and Description to help with
   search.
 - Fully qualified Source URL.
 - Updated to modern BuildRequires.
 - Separated %%build out into %%build and %%install.
 - Removed unnecessary references to buildroot.
 - Removed unnecessary %%defattr.
 - Changed Group from Web/Applications to Development/Libraries.
 - Removed hardcoded Packager tag.
 - Added %%check section.
 - Marked /etc/php.d/zmq.ini as a config file.
* Wed Jun 15 2011 Rick Moran <moran@morangroup.org>
 - Minor Changes.
* Thu Apr 8 2010 Mikko Koppanen <mkoppanen@php.net>
 - Initial spec file
