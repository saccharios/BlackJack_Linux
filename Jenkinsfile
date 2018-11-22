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
		
		step([$class: 'XUnitBuilder',  
			thresholds : [
			   [$class: 'FailedThreshold', failureThreshold: '1',  unstableThreshold: '0']
			   ],
			 tools : [
				[$class: 'GoogleTestType', pattern: 'build/UnitTest_release/unit_test_results.xml']]
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