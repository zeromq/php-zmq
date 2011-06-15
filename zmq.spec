# Define version and release number
%define version @PACKAGE_VERSION@
%define release 1

Name:          php-zmq
Version:       %{version}
Release:       %{release}%{?dist}
Packager:      Mikko Koppanen <mkoppanen@php.net>
Summary:       PHP 0MQ extension
License:       BSD License
Group:         Web/Applications
URL:           http://github.com/mkoppanen/php-zmq
Source:        zmq-%{version}.tgz
Prefix:        %{_prefix}
Buildroot:     %{_tmppath}/%{name}-%{version}-%{release}-root
BuildRequires: php-devel, make, gcc, /usr/bin/phpize, zeromq-devel >= 2.0.7
Requires:      zeromq >= 2.0.7

%description
PHP extension for 0MQ messaging system

%prep
%setup -q -n zmq-%{version}

%build
/usr/bin/phpize && %configure && %{__make} %{?_smp_mflags}

# Clean the buildroot so that it does not contain any stuff from previous builds
[ "%{buildroot}" != "/" ] && %{__rm} -rf %{buildroot}

# Install the extension
%{__make} install INSTALL_ROOT=%{buildroot}

# Create the ini location
%{__mkdir} -p %{buildroot}/%{_sysconfdir}/php.d

# Preliminary extension ini
echo "extension=zmq.so" > %{buildroot}/%{_sysconfdir}/php.d/zmq.ini

%clean
[ "%{buildroot}" != "/" ] && %{__rm} -rf %{buildroot}

%files
%defattr(-,root,root,-)
%{_libdir}/php/modules/zmq.so
%{_sysconfdir}/php.d/zmq.ini

%changelog
* Wed Jun 15 2011 Rick Moran <moran@morangroup.org>
 - Minor Changes.
* Thu Apr 8 2010 Mikko Koppanen <mkoppanen@php.net>
 - Initial spec file
