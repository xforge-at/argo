//
//  FileManagerTests.swift
//  ArgoLib
//
//  Created by Manu Wallner on 31.07.2016.
//
//

import XCTest
import Argo

class FileManagerTests: XCTestCase {
    var fileManager = FileManager()
    
    override func setUp() {
        super.setUp()
        // Put setup code here. This method is called before the invocation of each test method in the class.
    }
    
    override func tearDown() {
        // Put teardown code here. This method is called after the invocation of each test method in the class.
        super.tearDown()
    }
    
    func testKeyValueStorePath() {
        let path = fileManager.keyValueStorePath()
        
        XCTAssertNotEqual(path, "")
    }
    
}
