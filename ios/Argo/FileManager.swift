//
//  FileManager.swift
//  ArgoLib
//
//  Created by Michael Heinzl on 21.07.16.
//
//

import Foundation

open class FileManager: NSObject, XFFileManager {
	open func keyValueStorePath() -> String {
		let paths = NSSearchPathForDirectoriesInDomains(.applicationSupportDirectory, .userDomainMask, true)
		guard let path = paths.first else { return "" }
		return path
	}
}
