#!/usr/bin/env bash

set -e

# DVTFOUNDATION_DIR may vary depending on Xcode setup. Change it to reflect
# your current Xcode setup. Find suitable path with e.g.:
#
#	find / -type f -name 'DVTFoundation.xcplugindata' 2> /dev/null
#
# Example of DVTFOUNDATION_DIR's from "default" Xcode 4.x setups;
#
#	Xcode 4.1: /Developer/Library/PrivateFrameworks/DVTFoundation.framework/Versions/A/Resources/
#	Xcode 4.3: /Applications/Xcode.app/Contents/SharedFrameworks/DVTFoundation.framework/Versions/A/Resources/
#
DVTFOUNDATION_DIR="/Applications/Xcode.app/Contents/SharedFrameworks/DVTFoundation.framework/Versions/A/Resources/"
PLUGINDATA_FILE="DVTFoundation.xcplugindata"

PLISTBUDDY=/usr/libexec/PlistBuddy
PLIST_FILE=tmp.plist

# Provide means of deleting the OTD entry from the plugindata file.
if [ "$1" = "--delete-entry" ]; then
	echo "Removing OTD language specification entry."
	$PLISTBUDDY -c "Delete :plug-in:extensions:Xcode.SourceCodeLanguage.OTD" $DVTFOUNDATION_DIR/$PLUGINDATA_FILE
	echo "Run 'sudo rm -rf /var/folders/*' and restart Xcode to update change immediately."
	exit 0
fi

OTD_LANG_ENTRY="
	<?xml version=\"1.0\" encoding=\"UTF-8\"?>
	<!DOCTYPE plist PUBLIC \"-//Apple//DTD PLIST 1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\">
	<plist version=\"1.0\">
		<dict>
			<key>Xcode.SourceCodeLanguage.OTD</key>
			<dict>
				<key>conformsTo</key>
				<array>
					<dict>
						<key>identifier</key>
						<string>Xcode.SourceCodeLanguage.Generic</string>
					</dict>
				</array>
				<key>documentationAbbreviation</key>
				<string>otd</string>
				<key>fileDataType</key>
				<array>
					<dict>
						<key>identifier</key>
						<string>com.apple.xcode.otd-source</string>
					</dict>
				</array>
				<key>id</key>
				<string>Xcode.SourceCodeLanguage.OTD</string>
				<key>languageName</key>
				<string>OTD</string>
				<key>languageSpecification</key>
				<string>xcode.lang.otd</string>
				<key>name</key>
				<string>The OTD Documentation Language</string>
				<key>point</key>
				<string>Xcode.SourceCodeLanguage</string>
				<key>version</key>
				<string>1.0</string>
			</dict>
		</dict>
	</plist>
"

echo "Backing up plugindata file."
cp $DVTFOUNDATION_DIR/$PLUGINDATA_FILE $DVTFOUNDATION_DIR/$PLUGINDATA_FILE.bak

echo "Adding OTD language specification entry."
echo $OTD_LANG_ENTRY > $PLIST_FILE
$PLISTBUDDY -c "Merge $PLIST_FILE plug-in:extensions" $DVTFOUNDATION_DIR/$PLUGINDATA_FILE

rm -f $PLIST_FILE

echo "Installing OTD language specification file for Xcode."
cp otd.xclangspec $DVTFOUNDATION_DIR

echo "Run 'sudo rm -rf /var/folders/*' and restart Xcode to update change immediately."
echo "Syntax coloring must be manually selected from the Editor - Syntax Coloring menu in Xcode."
