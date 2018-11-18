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
    stage('build') {
      parallel {
        stage('build Simulations') {
          steps {
            sh 'scons Simulations'
          }
        }
        stage('build Simulations debug') {
          steps {
            sh 'scons --debug_build Simulations'
          }
        }
        stage('build Console Game') {
          steps {
            sh 'scons Console_Game'
          }
        }
        stage('build Console Game debug') {
          steps {
            sh 'scons --debug_build Console_Game'
          }
        }
		stage('build UnitTest') {
		  steps {
		    sh 'scons UnitTest'
          }
		}
		}
	}
  }
}