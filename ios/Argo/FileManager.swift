//
//  FileManager.swift
//  ArgoLib
//
//  Created by Michael Heinzl on 21.07.16.
//
//

import Foundation

public class FileManager: NSObject, XFFileManager {
	public func keyValueStorePath() -> String {
		let paths = NSSearchPathForDirectoriesInDomains(.ApplicationSupportDirectory, .UserDomainMask, true)
		guard let path = paths.first else { return "" }
		return path
	}
}