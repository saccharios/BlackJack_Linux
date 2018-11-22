pipeline {
  agent {
    dockerfile {
      filename 'Dockerfile'
    }

  }
  stages {
    stage('pyhton version') {
      steps {
        sh 'python --version'
        sh 'scons --version'
      }
    }
    stage('build UnitTest') {
      steps {
        sh 'scons UnitTest'
      }
    }
    stage('Test') {
      steps {
        sh 'cd build/UnitTest_release && ./UnitTest --gtest_output=xml:unit_test_results.xml'
		
		step([$class: 'XUnitBuilder', testTimeMargin: '3000', thresholdMode: 1
			thresholds : [
			   [$class: 'FailedThreshold', failureNewThreshold: '', failureThreshold, '0', unstableNewThreshold '', unstableThreshold '']
			   [$class: 'SkippedThreshold', failureNewThreshold: '', failureThreshold, '0', unstableNewThreshold '', unstableTrheshold '']],
			 tools : [
				[$class: 'GoogleTestType', deleteOutputFiles: true, failIfNotNew: true, pattern: 'build/UnitTest_release/unit_test_results.xml', skipNoTestFiles: false, stopProcessingIfError: true]]
		])
      }
    }
  }
  post {
	always {
		archiveArtifacts artifacts: 'build/UnitTest_release/UnitTest*', fingerprint: true
		archiveArtifacts artifacts: 'build/UnitTest_release/*xml', fingerprint: true
	}
  }
}